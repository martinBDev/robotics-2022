from flask import Flask
import requests

URL_ARDUINO = "https://ip/algoQueHagaElArduino?param"
URL = "http://maps.googleapis.com/maps/api/geocode/json"

# defining a params dict for the parameters to be sent to the API
location = "delhi technological university"
PARAMS = {'address':location}

app = Flask(__name__)

@app.route('/')
def hello():
    # sending get request and saving the response as response object
    r = requests.get(url = URL, params = PARAMS)
    data = r.json()
    return data