
 async function askArduino(ip){
     
  const response = await callApi(ip, "medir")

  
  var jsonContent = await response.json()
  console.log(jsonContent)
  return "Humidity: " + jsonContent.humidity + ", temperature: " + jsonContent.temperature

}


async function interactuarLed(ip){
    const response = await callApi(ip, "interactuarLed")

  
  var jsonContent = await response.json()
  console.log(jsonContent)
  document.getElementById(ip).value = jsonContent.encendido
  return "Encendido: "  + jsonContent.encendido

}


async function ledState(ip){
  const response = await callApi(ip, "ledState")

  
  var jsonContent = await response.json()
  console.log(jsonContent)
  document.getElementById(ip).value = jsonContent.ledState
  return "Estado led: "  + jsonContent.ledState
}



async function callApi(ip, param){
  var url = "http://"+ip+"/" + param; //CAMBIAR URL PARA OBTENER DATOS DEL ARDUINO
  const response = await fetch(url, {
    method: 'GET',
    mode: 'cors',
    headers: {
      accept: 'application/json',
    },
  });

  return response;
}

function updatePlacesCards(){

  locations.forEach(location => {
    let strHTML = '<div class="column">';
    strHTML += '<img src="https://cassi.uniovi.es/cas/themes/uniovi_theme/images/uniovi_solo_escudo_color.png" alt="Avatar" ><div class="container">'
    strHTML += '<h4><b>'+ location.title + '</b></h4> ' + ' <p>'+ location.ip+'</p> <br>' + ' <p>'+ location.coord+'</p> ' + '</div> </div>'
    $('#allCards').append(strHTML)
  })   
      
}

updatePlacesCards();

