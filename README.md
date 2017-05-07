# NeoPixel-Chandelier
Apartments are a hard place to live in at times, as they may not always be the best lit.  Such is the case of my apartments living room.  So I set out to fix that, thus the chandelier was born.  I was looking for an item, that would easily work with my existing home network, easy to control, bright and looks cool.  

The design is something that I have been toying with for quit a while.  There is just something pleasing and appealing of the older fashion glass bottles.  So when I was cleaning out an area lately I came across several old bottles, and some older wood.  Combining both of these together, I finally saw my dream become reality.  I had the bottles cleaned up, and the wood distressed to give it a little more aged look.

The chandelier is using Several Adafruit Neopixels to light up multiple layers.  It is using the following:<br>
2x- Neopixel strips<br>
4x- Neopixel quarter ring<br>
6x- Individual neopixels hooked in sequence<br>
1x- Individual neopixel<br>

The lighting design has the two strips running around the top outside portion.  These can be controlled together to give it a unique full look.  My 4 quarter peices make up a full circle which is connnected underneth the chandelier, wrapping around a center bottle.  I have 6 bottles that go around the outside of the design, and then one final central bottle.  Each bottle has its own individual Neopixel.  The 6 outside are connected in sequence, and the central bottle is left seperate.

The whole setup is controlled by an Adafruit ESP8266 Feather.  Commands are received as MQTT messages on a single thread, and the payload is broken apart to determine the actual action.  I am using a 9v power supply to supply the whole thing.
