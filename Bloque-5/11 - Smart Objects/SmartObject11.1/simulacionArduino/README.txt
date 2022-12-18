Paso 0: instalar entorno virtual:
		py -3 -m pip install virtualenv
Paso 1: crear virtual environment: 
        py -3 -m venv <name of environment>
Paso 2: activar environment:
        <name of environment>\Scripts\activate
Paso 3: dentro del entorno virtual, instalar flask  y requests: 
        pip install flask
        pip install requests
        pip install flask-cors
Paso 4: variable de entorno FLASK_APP: 
        setx FLASK_APP "<archivo>.py"
Paso 5: ejecutar app de flask:
        flask run --host=0.0.0.0


IMPORTANTE AÑADIR "--host=0.0.0.0" AL INICIAR EL SERVIDOR,
PARA QUE SEA EXTERNAMENTE VISIBLE A TODA LA RED LOCAL.

INFO: tutorial en https://phoenixnap.com/kb/install-flask
