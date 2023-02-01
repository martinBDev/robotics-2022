 #AUTORES:
  #Martin Beltran Diaz - UO276244
  #Stelian Adrian Stanci - UO277653
  #Laura Pernia Blanco - UO276264

from flask import Flask, Response, jsonify
import requests
from flask_cors import CORS

URL_ARDUINO = "https://ip/algoQueHagaElArduino?param"
URL = "http://maps.googleapis.com/maps/api/geocode/json"

# defining a params dict for the parameters to be sent to the API
location = "delhi technological university"
PARAMS = {'address':location}

app = Flask(__name__)
CORS(app)




@app.route('/medir')
def hello():
    return jsonify(
        temperature=16,
        humidity=90,
        led=True
    )
    # sending get request and saving the response as response object
   # r = requests.get(url = URL, params = PARAMS)
    #r = {'temperature':14, 'humidity':34}
    
    
    #return Response(r, mimetype='application/json')

@app.route('/interactuarLed')
def encender():
    return jsonify(
        led=True
    )