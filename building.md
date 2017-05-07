Required parts:<br>
1) Adafruit ESP8266 Feather https://www.adafruit.com/product/2821
2) Adafruit 8 channel bi-directional logic converter https://www.adafruit.com/product/395
3) DC Barrel Jack https://www.adafruit.com/product/373
4) Compacitor
5) Resistors
6) Neopixels
7) Hookup wire
8) Power Supply
9) Male Headers
10) Female headers
11) Perma-Proto breadboard https://www.adafruit.com/product/1609

Tools:
1) Soldering Iron
2) Solder
3) Wire Strippers
4) Helping Hand

**WARNING: YOU WILL BE SOLDERING A CONNECTION TO THE USB PIN. DO NOT UNDER ANY CIRCUMSTANCE HAVE IT CONNECTED TO THE POWER SUPPLY AND PLUG IN A USB CABLE.**

Instructions:
1) Solder the male headers to the logic converter and Feather.
2) Test fit everything on your perma-proto board.  You have to make sure that the feather, logic converter, and barrel jack all fit with additional room for wiring.
3) Once in everything fits, use tap, or blutac to hold in place the logic converter and barrel jack.  Solder these onto your board.
4) Replace your feather with the female headers.  Hold these in position with either tape or blutac, then solder them in.
5) Solder a wire connection between the positive and negative terminals of your barrel jack to the positive and negative rails on the board.
6) Solder a connection between the positive rail and the USB pin of the feather.  Solder a connection between the negative rail and GND pin on the feather.
7) Solder a connection between the 3V pin on the feather and the VCCA of the logic converter.
8) Solder a connection between the positive rail and the VCCB of the logic converter.  Solder another connection between the negative rail and GND of the logic converter.
9) Using any of the GPIO pins on the feather, solder a connection to the A side of the logic converter.<br>
**THIS COMPLETES THE SOLDERING AND CONSTRUCTION OF THE MAIN BOARD**

10) Solder the compacitor to the positive and negative rails on a second perma-proto board.  Make sure you get the legs correctly, as putting it in backwards could have catastropic effects.
11) Solder a connection from the positive and negative rails from the first board to second board.  These connections should be made directly in front of the compacitor.
12) Solder in resistors across the middle of your perma-proto board.  Use as many resistors as you need.  Each pixel section needs its own resistor.
  12A) The resistors need to be soldered across the middle of the board, that way they will each have their own rails, and not be on the same rail.
13) Solder a connection from the "B" side of the logic converter, to your resistors.
14) Solder a connection between your positive, negative rails and the positive and negative on the pixels.  Then solder a connection between the resistor and data in on the pixels.
