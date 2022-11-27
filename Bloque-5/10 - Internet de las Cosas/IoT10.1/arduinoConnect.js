  //AUTORES:
  //Martin Beltran Diaz - UO276244
  //Stelian Adrian Stanci - UO277653
  //Laura Pernia Blanco - UO276264
 async function askArduino(ip){
   
  var jsonContent = retreiveData(ip)
  return "Humidity: " + jsonContent.humidity + ", temperature: " + jsonContent.temperature

}

async function retreiveData(ip){
  const response = await callApi(ip, "medir")

  
  var jsonContent = await response.json()
  console.log(jsonContent)
  return jsonContent;
}


async function interactuarLed(ip){
    const response = await callApi(ip, "interactuarLed")

  
  var jsonContent = await response.json()
  console.log(jsonContent)
  $('#ledState').text(jsonContent.led);
  
  return "Encendido: "  + jsonContent.led

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


