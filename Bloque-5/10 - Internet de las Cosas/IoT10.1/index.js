  //AUTORES:
  //Martin Beltran Diaz - UO276244
  //Stelian Adrian Stanci - UO277653
  //Laura Pernia Blanco - UO276264

'use strict';

/** Hide a DOM element. */
function hideElement(el) {
  el.style.display = 'none';
}

/** Show a DOM element that has been hidden. */
function showElement(el) {
  el.style.display = 'block';
}

/** Helper function to generate a Google Maps directions URL */
function generateDirectionsURL(origin, destination) {
  const googleMapsUrlBase = 'https://www.google.com/maps/dir/?';
  const searchParams = new URLSearchParams('api=1');
  searchParams.append('origin', origin);
  const destinationParam = [];
  // Add title to destinationParam except in cases where Quick Builder set
  // the title to the first line of the address
  if (destination.title !== destination.address1) {
    destinationParam.push(destination.title);
  }
  destinationParam.push(destination.address1, destination.address2);
  searchParams.append('destination', destinationParam.join(','));
  return googleMapsUrlBase + searchParams.toString();
}

/**
 * Defines an instance of the Locator+ solution, to be instantiated
 * when the Maps library is loaded.
 */
function LocatorPlus(configuration) {
  const locator = this;

  locator.locations = configuration.locations || [];
  locator.capabilities = configuration.capabilities || {};

  const mapEl = document.getElementById('gmp-map');
  const panelEl = document.getElementById('locations-panel');
  locator.panelListEl = document.getElementById('locations-panel-list');
  const sectionNameEl =
      document.getElementById('location-results-section-name');
  const resultsContainerEl = document.getElementById('location-results-list');

  const itemsTemplate = Handlebars.compile(
      document.getElementById('locator-result-items-tmpl').innerHTML);

  locator.searchLocation = null;
  locator.searchLocationMarker = null;
  locator.selectedLocationIdx = null;
  locator.userCountry = null;

  // Initialize the map -------------------------------------------------------
  locator.map = new google.maps.Map(mapEl, configuration.mapOptions);

  // Store selection.
  const selectResultItem = function(locationIdx, panToMarker, scrollToResult) {
    locator.selectedLocationIdx = locationIdx;
    for (let locationElem of resultsContainerEl.children) {
      locationElem.classList.remove('selected');
      if (getResultIndex(locationElem) === locator.selectedLocationIdx) {
        locationElem.classList.add('selected');
        if (scrollToResult) {
          panelEl.scrollTop = locationElem.offsetTop;
        }
      }
    }
    if (panToMarker && (locationIdx != null)) {
      locator.map.panTo(locator.locations[locationIdx].coords);
    }
  };

  var infoWindow = null;
  // Create a marker for each location.
  const markers = locator.locations.map(function(location, index) {
    const marker = new google.maps.Marker({
      position: location.coords,
      map: locator.map,
      title: location.title,
    });

    //MODIFICADO PARA PEDIR DATOS AL ARDUINO//////////////////////////////////
    var contentString = "Loading...";
 
    
    marker.addListener('click',async  function() {

      if(infoWindow){
        infoWindow.close();
      }
     

      var buttonStr = "<button class=\"LED-button\" title=\"Encender LED del arduino\" id=\"" + location.ip + "\" onclick=interactuarLed(\"" + location.ip + "\") style=\"border-color: lightskyblue;border-radius: 8%;border-width: 2.3em;background-color: chartreuse;color: black;\"> LED encendido: </button>"
      
      var arduinoState = await retreiveData(location.ip); 
      contentString = buttonStr + "<br/> <div id=\"ledState\">" + arduinoState.led + "</div>"; 
    
//ACTUALIZA HUMEDAD
      if(arduinoState.humidity > CONFIGURATION.alerts.humidity && !arduinoState.led){ //si se supera el limite y aun no se encendio el led
        
        contentString +=  "<br/> Humidity: <div id=\"humiduty\" style=\"color:red;\"><b>"  + arduinoState.humidity + "%</b></div>"
      }else if (arduinoState.humidity > CONFIGURATION.alerts.humidity){ //LOS DATOS ESTAN altos pero se encendio el led de aviso
        contentString +=  "<br/> Humidity: <div id=\"humiduty\" style=\"color:orange;\"><b>"  + arduinoState.humidity + "%</b></div>"
      }else{ //datos altos y el led no encendido
        contentString +=  "<br/> Humidity: <div id=\"humiduty\" style=\"color:green;\"><b>"  + arduinoState.humidity + "%</b></div>"
      }


//ACTUALIZA TEMPERATURA
      if(arduinoState.temperature > CONFIGURATION.alerts.temperature && !arduinoState.led){ //si se supera el limite y aun no se encendio el led
        
        contentString +=  "Temperature: <div id=\"temperature\" style=\"color:red;\"><b>"  + arduinoState.temperature + "ºC</b></div>"
      }else if (arduinoState.temperature > CONFIGURATION.alerts.temperature){ //LOS DATOS ESTAN altos pero se encendio el led de aviso
        contentString +=  "Temperature: <div id=\"temperature\" style=\"color:orange;\"><b>"  + arduinoState.temperature + "ºC</b></div>"
      }else{ //datos altos y el led no encendido
        contentString +=  "Temperature: <div id=\"temperature\" style=\"color:green;\"><b>"  + arduinoState.temperature + "ºC</b></div>"
      }

     

      
      infoWindow = new google.maps.InfoWindow({
        content: contentString,
        ariaLabel: "Uluru",
      });
      infoWindow.open({
        anchor: marker,
        map: locator.map,
      });
    });
    return marker;
  });
//////////////////////////////////////////////////////////////////
  // Fit map to marker bounds.
  locator.updateBounds = function() {
    const bounds = new google.maps.LatLngBounds();
    if (locator.searchLocationMarker) {
      bounds.extend(locator.searchLocationMarker.getPosition());
    }
    for (let i = 0; i < markers.length; i++) {
      bounds.extend(markers[i].getPosition());
    }
    locator.map.fitBounds(bounds);
  };
  if (locator.locations.length) {
    locator.updateBounds();
  }

  // Get the distance of a store location to the user's location,
  // used in sorting the list.
  const getLocationDistance = function(location) {
    if (!locator.searchLocation) return null;

    // Fall back to straight-line distance.
    return google.maps.geometry.spherical.computeDistanceBetween(
        new google.maps.LatLng(location.coords),
        locator.searchLocation.location);
  };

  // Render the results list --------------------------------------------------
  const getResultIndex = function(elem) {
    return parseInt(elem.getAttribute('data-location-index'));
  };

  locator.renderResultsList = function() {
    let locations = locator.locations.slice();
    for (let i = 0; i < locations.length; i++) {
      locations[i].index = i;
    }
    if (locator.searchLocation) {
      sectionNameEl.textContent =
          'Nearest locations (' + locations.length + ')';
      locations.sort(function(a, b) {
        return getLocationDistance(a) - getLocationDistance(b);
      });
    } else {
      sectionNameEl.textContent = `All locations (${locations.length})`;
    }
    const resultItemContext = {locations: locations};
    resultsContainerEl.innerHTML = itemsTemplate(resultItemContext);


    for (let item of resultsContainerEl.children) {
      const resultIndex = getResultIndex(item);
      if (resultIndex === locator.selectedLocationIdx) {
        item.classList.add('selected');
      }

      const resultSelectionHandler = function() {
        if (resultIndex !== locator.selectedLocationIdx) {
          selectResultItem(resultIndex, true, false);
        }
      };

      // Clicking anywhere on the item selects this location.
      // Additionally, create a button element to make this behavior
      // accessible under tab navigation.
      item.addEventListener('click', resultSelectionHandler);
      item.querySelector('.select-location')
          .addEventListener('click', function(e) {
            resultSelectionHandler();
            e.stopPropagation();
          });

      // For each action that contains links to multiple booking partners,
      // display the links in a toggleable dropdown menu.
      item.querySelectorAll('.dropdown-container').forEach((containerEl) => {
        const dropdownEl = containerEl.querySelector('.action-dropdown');
        const dropdownToggleEl =
            containerEl.querySelector('.action-dropdown-toggle');
        dropdownToggleEl.addEventListener('click', function(e) {
          // First check if any dropdown menu is open and close it.
          if (locator.openDropdownEl) {
            hideElement(locator.openDropdownEl);
            if (locator.openDropdownEl === dropdownEl) {
              locator.openDropdownEl = undefined;
              return;
            }
          }
          showElement(dropdownEl);
          locator.openDropdownEl = dropdownEl;
        });
      });

      // Clicking the directions button will open Google Maps directions in a
      // new tab
      const origin = (locator.searchLocation != null) ?
          locator.searchLocation.location :
          '';
      const destination = locator.locations[resultIndex];
      const googleMapsUrl = generateDirectionsURL(origin, destination);
      item.querySelector('.directions-button')
          .setAttribute('href', googleMapsUrl);

  
      console.log(locator.locations[resultIndex])
    }
  };

  window.addEventListener('click', function(e) {
    // Collapse any open dropdown menu when user clicks outside it.
    if (locator.openDropdownEl && !locator.openDropdownEl.parentNode.contains(e.target)) {
      hideElement(locator.openDropdownEl);
      locator.openDropdownEl = undefined;
    }
  });

  // Optional capability initialization --------------------------------------
  initializeSearchInput(locator);

  // Initial render of results -----------------------------------------------
  locator.renderResultsList();
}

/** When the search input capability is enabled, initialize it. */
function initializeSearchInput(locator) {
  const geocodeCache = new Map();
  const geocoder = new google.maps.Geocoder();

  const searchInputEl = document.getElementById('location-search-input');
  const searchButtonEl = document.getElementById('location-search-button');

  const updateSearchLocation = function(address, location) {
    if (locator.searchLocationMarker) {
      locator.searchLocationMarker.setMap(null);
    }
    if (!location) {
      locator.searchLocation = null;
      return;
    }
    locator.searchLocation = {'address': address, 'location': location};
    locator.searchLocationMarker = new google.maps.Marker({
      position: location,
      map: locator.map,
      title: 'My location',
      icon: {
        path: google.maps.SymbolPath.CIRCLE,
        scale: 12,
        fillColor: '#3367D6',
        fillOpacity: 0.5,
        strokeOpacity: 0,
      }
    });

    // Update the locator's idea of the user's country, used for units. Use
    // `formatted_address` instead of the more structured `address_components`
    // to avoid an additional billed call.
    const addressParts = address.split(' ');
    locator.userCountry = addressParts[addressParts.length - 1];

    // Update map bounds to include the new location marker.
    locator.updateBounds();

    // Update the result list so we can sort it by proximity.
    locator.renderResultsList();
  };

  const geocodeSearch = function(query) {
    if (!query) {
      return;
    }

    const handleResult = function(geocodeResult) {
      searchInputEl.value = geocodeResult.formatted_address;
      updateSearchLocation(
          geocodeResult.formatted_address, geocodeResult.geometry.location);
    };

    if (geocodeCache.has(query)) {
      handleResult(geocodeCache.get(query));
      return;
    }
    const request = {address: query, bounds: locator.map.getBounds()};
    geocoder.geocode(request, function(results, status) {
      if (status === 'OK') {
        if (results.length > 0) {
          const result = results[0];
          geocodeCache.set(query, result);
          handleResult(result);
        }
      }
    });
  };

  // Set up geocoding on the search input.
  searchButtonEl.addEventListener('click', function() {
    geocodeSearch(searchInputEl.value.trim());
  });

  // Add in an event listener for the Enter key.
  searchInputEl.addEventListener('keypress', function(evt) {
    if (evt.key === 'Enter') {
      geocodeSearch(searchInputEl.value);
    }
  });
}