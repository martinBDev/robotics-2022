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
        humidity=12,
        led=1
    )
    # sending get request and saving the response as response object
   # r = requests.get(url = URL, params = PARAMS)
    #r = {'temperature':14, 'humidity':34}
    
    
    #return Response(r, mimetype='application/json')

@app.route('/interactuarLed')
def encender():
    return jsonify(
        encendido=True
    )

