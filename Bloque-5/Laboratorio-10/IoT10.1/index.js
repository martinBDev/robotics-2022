let map;
let contentString = "loading...";

function askArduino(){
    var xhr = new XMLHttpRequest();
    var url = "http://ip/medir";

    xhr.open("GET", url, true);
    xhr.setRequestHeader("Content-Type", "application/json");
    xhr.onreadystatechange = function () {
        if (xhr.readyState === 4 && xhr.status === 200) {
            var json = JSON.parse(xhr.responseText);
            console.log(json.email + ", " + json.password);
            contentString = "Humidity: " + json.humidity + " - " + "Temperature: " + json.temperature;
        }
    };
    xhr.send();
}

function initMap() {
  map = new google.maps.Map(document.getElementById("map"), {
    center: { lat: -34.397, lng: 150.644 },
    zoom: 8,
  });
  

const infowindow = new google.maps.InfoWindow({
  content: contentString,
  ariaLabel: "Uluru",
});

const marker = new google.maps.Marker({
  position: uluru,
  map,
  title: "Uluru (Ayers Rock)",
});

marker.addListener("click", () => {
    askArduino();
  infowindow.open({
    anchor: marker,
    map,
  });
});
}

window.initMap = initMap;
