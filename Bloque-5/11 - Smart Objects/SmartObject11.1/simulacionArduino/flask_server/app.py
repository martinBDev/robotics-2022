 #AUTORES:
  #Martin Beltran Diaz - UO276244
  #Stelian Adrian Stanci - UO277653
  #Laura Pernia Blanco - UO276264

from flask import Flask, Response, jsonify, request, render_template
import requests
from flask_cors import CORS

URL_ARDUINO = "http://192.168.0.207/"
validUids = ["83130224167"] #Simulamos la BD de usuarios, cuando hagamos el ejercicio de la raspberry no se simulará


app = Flask(__name__)
CORS(app)


@app.route("/")
def hel():
    return render_template('page.html', state="Iniciando");

@app.route('/checkUser')
def checkUser():
    id = request.args.get('uuid')
    print(id)
    if(id in validUids):
        r =requests.get(URL_ARDUINO+ "userAccepted?true")
        return render_template('page.html', state="Funcionando");
       # return Response({"accepted":True}, mimetype='application/json')

    else:
        r =requests.get(URL_ARDUINO+ "userAccepted?false")
        return render_template('page.html', state="Funcionando");
        #return Response({"accepted":False}, mimetype='application/json')




@app.route('/bloquear')
def bloquear():
    r =requests.get(URL_ARDUINO+ "bloquear")
    return render_template('page.html', state="Bloqueado");

@app.route('/abrir')
def abrir():
    r =requests.get(URL_ARDUINO+ "abrir")
    return render_template('page.html', state="Abierto");

@app.route('/restaurar')
def restaurar():
    r =requests.get(URL_ARDUINO+ "restaurar")
    return render_template('page.html', state="Funcionando");
