# ColorDice
Dado electrónico de colores con Arduino y LEDs y sistema inercial para detectar la cara que ha caido.

##Electrónica

- Arduino Nano
- [Shield Arduino Nano](https://es.aliexpress.com/item/33063354279.html?spm=a2g0s.9042311.0.0.3c4463c0q9bBWU)
- [Tira de LEDs indexados WS2811 5V 60Leds/M IP30 ](https://es.aliexpress.com/item/2000165819.html)
- [Acelerómetro IMU MPU9250](https://es.aliexpress.com/item/4000284459476.html)
- Interruptor basculante
- Pila 9V 

![NanoShield_b][NanoShield_b]
![MPU9250_Library][MPU9250_Library]
![Switch][Switch]


## Cableado

![Montaje Electrónico][MontajeNanoShieldWithMPU]

## Piezas

![Cubo_interno][cubo_interno]

## Librerías necesarias

Se requieren instalar las librerías:
- [Adafruit Neopixel](https://github.com/adafruit/Adafruit_NeoPixel)
- [MPU9250](https://github.com/hideakitai)

Se encuentran disponibles en el repositorio oficial de Arduino

![MPU9250_Library][MPU9250_Library]
![NeoPixel_Library][NeoPixel_Library]

## Montaje paso a paso


[cubo_interno]: /src/img/cubo_interno.jpg
[MontajeNanoShieldWithMPU]: /src/img/CuboEmocionesNanoShieldWithMPU_bb.png
[MPU9250]: /src/img/MPU9250.png
[NanoShield_b]: /src/img/NanoShield_b.png
[Switch]: /src/img/Switch.jpg
[MPU9250_Library]: /src/img/MPU9250_Library.png
[NeoPixel_Library]: /src/img/NeoPixel_Library.png