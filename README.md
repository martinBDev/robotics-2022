# 🤖 ROBOTICS 2022

## 🦾 Bloque 1

### 🎲 Dado 1.1
<details>
    <summary>Enunciado</summary>
    <br>
    Habrá que simular un dado electrónicamente. Para ello, se utilizarán 3 LEDs y un pulsador.
    Inicialmente, todos los LEDs estarán apagados. Cuando se presione el pulsador, el sistema
    generará un número aleatorio entre 1 y 3. El número obtenido se mostrará al usuario
    encendiendo los LEDs. Los LEDs se deben situarse en línea, y deberán encenderse siempre de
    forma ordenada: primero los encendidos y luego los apagados, es decir, no mezclados.

</details>
<ul>
    <li> Código: ✅</li>
    <li> Fotografía: ✅</li>
    <li> Vídeo: ❌</li>
    <li> Documentación:  ✅</li>
</ul>

### 🧠 Memoria 1.2
<details>
    <summary>Enunciado</summary>
    <br>
    En este ejercicio se creará un juego como el «Simón». Como máximo deberá tener 3
    turnos, es decir, la secuencia más larga será de 5 colores. Sin embargo, esto tiene que ser
    modificable fácilmente a nivel de código (una variable), y mostrarlo en el vídeo.
    <br><br>
    Cuando iniciamos la aplicación se debe generar una secuencia aleatoria (de verdad y
    demostrada en el video). Esta secuencia comenzará con 3 opciones, que serán en función de la
    secuencia aleatoria que se obtuvo. Se recomiendo utilizar una estructura de datos, como puede ser array, para almacenar las secuencias. Por ejemplo, esta secuencia podría ser: Verde-RojoVerde, Verde-Verde-Verde, Rojo-Rojo-Rojo, Rojo-Verde-Verde, etc. Entre cada parpadeo se
    debe esperar un segundo. Tras esto, hay que esperar un par de segundos y comenzará el usuario
    a introducirla.<br><br>
    En este momento es cuando el usuario debe reproducir esa secuencia utilizando los
    pulsadores. Un pulsador se corresponderá al rojo y el otro al verde. Es decir, para «acertar» la
    secuencia Verde, Rojo, Verde el usuario deberá pulsar el pulsador asociado al verde una vez,
    después el pulsador asociado al rojo y tras esto el pulsador asociado al verde una vez. Cuando
    se pulse un pulsador, el LED asociado a ese pulsador se deberá iluminar.<br><br>
    Si el usuario realiza la acción correctamente, el juego sube de nivel. El incremento de nivel
    implica añadir un nuevo color generado aleatoriamente a la secuencia previa. Cada vez que el
    usuario acierta la combinación se vuelve a repetir la secuencia anterior añadiendo un parpadeo
    adicional para así ir aumentando la dificultad. ¡Ojo! Se añade un nuevo color a la secuencia
    previa, no hay que generar una nueva secuencia entera. Cuando llegué al final y el usuario
    obtenga la victoria, se mostrará un efecto de luz especial que indicará la victoria del usuario.<br><br>
    Si el usuario se equivoca y realiza una pulsación incorrecta, el juego finalizará, se mostrará
    un efecto de luz que indicará el fin de la partida (diferente al de la victoria) y se volverá a iniciar
    desde el principio. Se debe volver a generar una secuencia aleatoria inicial nueva.<br><br>
    Se debe dividir la funcionalidad del sistema en funciones. Si toda la lógica se encuentra en
    el método «loop», se restará la mitad de puntos, aunque el ejercicio esté bien.<br><br>
    ¡Cuidado! Los pulsadores necesitan de una resistencia, así que hay que añadirla, pues,
    en el caso de que quedaran conectadas directamente las corrientes positivas y negativa se haría
    un cortocircuito y se podría quemar la placa.<br><br>
    Atención: cuando se grabe el video, hay que mostrar tres secuencias/rondas, en dos
    partidas, una en la que funcione bien y otra partida en la que se falle en la segunda secuencia,
    para ver cómo se reinicia el juego. Habrá que mostrar varios inicios del primer turno para
    enseñar que el aleatorio se hizo correctamente. Si no, se descontarán puntos.

</details>
<ul>
    <li> Código: ✅</li>
    <li> Fotografía: ✅</li>
    <li> Vídeo: ✅</li>
    <li> Documentación:  ✅</li>
</ul>

### 🚥 Semaforo 1.4
<details>
    <summary>Enunciado</summary>
    <br>
    En este ejercicio hay que implementar un cruce con dos semáforos. Para ello, cuando un
    semáforo esté en verde, el otro estará en rojo. Después de un tiempo, el semáforo que está en
    verde tendrá que pasar a amarillo, y, tras unos segundos, a rojo. Tras una breve pausa para
    esperar a que los coches terminen de cruzar, el otro deberá de ponerse en verde y repetir el
    mismo proceso.

</details>
<ul>
    <li> Código: ✅</li>
    <li> Fotografía: ✅</li>
    <li> Vídeo: ❌</li>
    <li> Documentación:  ✅</li>
</ul>


### 🚥👨‍🦯 Semaforo 1.5
<details>
    <summary>Enunciado</summary>
    <br>
    Este ejercicio es una ampliación sobre el ejercicio anterior, cambiando algún componente
    y añadiendo un paso para peatones.<br><br>
    Habrá que cambiar los LEDs de los semáforos a LEDs RGB. Seguirá habiendo dos
    semáforos, pero solo uno tendrá paso para peatones.<br><br>
    Para el paso de peatones, habrá que utilizar el LED verde, el LED rojo, y el zumbador. El
    LED rojo estará encendido cuando el semáforo para coches correspondiente esté en verde.
    Cuando este esté en rojo, y después de un tiempo, para evitar atropellos, se encenderá el LED
    verde para peatones y el zumbador hará pitidos para que las personas ciegas sepan cuando
    cruzar. Cuando quede poco tiempo, el LED verde deberá de parpadear y los sonidos ir un poco
    más rápido. Una vez se ponga en rojo y tras unos segundos, se abrirá el tráfico a los coches en
    la vía correspondiente.


</details>
<ul>
    <li> Código: ✅</li>
    <li> Fotografía: ✅</li>
    <li> Vídeo: ❌</li>
    <li> Documentación:  ✅</li>
</ul>


### 🕺 Discoteca 1.6
<details>
    <summary>Enunciado</summary>
    <br>
    Se tratará de hacer un sistema para que el DJ pueda cambiar las tonalidades de las luces y el volumen a su gusto. Para ello, se usarán dos potenciómetros.<br><br>
    Un potenciómetro controlará las luces, en nuestro caso, son LEDs RGB. Cuando esté en su valor mínimo, un LED RGB estará apagado y el otro estará iluminando con todos los colores a tope. Según se vaya creciendo el valor del potenciómetro, el LED RGB apagado irá encendiéndose, haciendo una escala de colores (arcoíris y de forma libre y comenzando en 000 y terminando los colores en 255) y el segundo LED hará justamente lo contrario. En el valor central del potenciómetro ambos LEDs RGB deberán de tener la misma tonalidad.<br><br>
    El segundo potenciómetro controlará las notas musicales. El valor mínimo no hará ruido y el máximo hará una de las notas más altas en la escala musical.<br><br>
    Como se necesitarán 7 salidas digitales PWM y en el Arduino UNO solo hay 6, hay tres posibilidades para hacer este ejercicio:<br><br>
        • Pedir prestada la plaza Arduino Mega.<br>
        • Usar un transistor.<br>
        • «Trampearlo» usando una salida para dos LEDs.<br>

</details>
<ul>
    <li> Código: ✅</li>
    <li> Fotografía: ✅</li>
    <li> Vídeo: ❌</li>
    <li> Documentación:  ✅</li>
</ul>



### 🦃 Regulador 1.7
<details>
    <summary>Enunciado</summary>
    <br>
    Conectar 3 LEDs y un potenciómetro. En función del valor de entrada del potenciómetro se tendrán que encender 0, 1, 2 o los 3 LEDs de forma secuencial, empezando por el 0 y siguiendo el orden. En este caso, todos los LEDs deben encenderse siempre con la misma intensidad, es decir, estarán apagados o encendidos.<br><br>
La secuencia de encendido es: se encienda primero el A, después el B, después el C, después A y B, después B y C, después A y C, y cuando esté en el máximo valor los 3.<br><br>

</details>
<ul>
    <li> Código: ✅</li>
    <li> Fotografía: ✅</li>
    <li> Vídeo: ❌</li>
    <li> Documentación:  ❌</li>
</ul>

### 🎖️ Regulador 1.8
<details>
    <summary>Enunciado</summary>
    <br>
    Conectar 3 LEDs y un potenciómetro. En función del valor de entrada del potenciómetro se tendrán que encender 0, 1, 2 o los 3 LEDs. No obstante, en este caso, cuando más cercano esté del límite inferior, menos luminosidad tendrán los LED y cuantos más cercanos al límite superior tendrán más luminosidad. Utilizar las salidas PWM para encenderlos.<br><br>

</details>
<ul>
    <li> Código: ✅</li>
    <li> Fotografía: ✅</li>
    <li> Vídeo: ✅</li>
    <li> Documentación:  ✅</li>
</ul>

