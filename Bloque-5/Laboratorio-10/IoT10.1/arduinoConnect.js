
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
  $('#ledState').text(jsonContent.encendido);
  
  return "Encendido: "  + jsonContent.encendido

}


async function ledState(ip){
  const response = await callApi(ip, "ledState")

  
  var jsonContent = await response.json()

  
  console.log(jsonContent)
  return jsonContent.ledState
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
