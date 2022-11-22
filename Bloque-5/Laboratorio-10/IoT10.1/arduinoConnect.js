let map;
let contentString = "loading...";

async function askArduino(){
    
    var url = "http://localhost:5000/";
    const response = await fetch(url, {
      method: 'GET',
      mode: 'cors',
      headers: {
        accept: 'application/json',
      },
    });

    
    var jsonContent = await response.json()
    console.log(jsonContent)
    /* xhr.onreadystatechange = function () {
        if (xhr.readyState === 4 && xhr.status === 200) {
            var json = JSON.parse(xhr.responseText);
            console.log(json.humidity + ", " + json.temperature);
            contentString = "Humidity: " + json.humidity + " - " + "Temperature: " + json.temperature;
        }
    }; */
}
document.getElementById("clickMe").onclick = askArduino;
/* 
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

window.initMap = initMap; */
