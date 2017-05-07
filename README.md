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

As mentioned it using MQTT topics and payload for control.  It has a current topic that is subscribes to, and when a payload is published on said topic it will break it apart for to control the lights.  I have it written were it needs to be done in a specific fashion, or else it could cause unwanted results.  Two different types of payloads are also required.  One lets you turn it on and off; the other is for animations.

paylod for control:
c:on/off:all/pin<br>
the "c" tells it that it will be a control message.  "on"/"off" tell it what to do, and the "all" or "pin" tell it what lights to work with.  If you give it a number for pin, then it will be that specific set.  If you use all it will be all the lights at once.

a:pattern:pin:r:g: b :r:g:b <br>
The "a" tells us that it will be patterns.  I have setup some specific patterns that use a shortened version that we will send using the payload.  The "pattern" tells the program what to show.  "pin" is linked to a specific set of lights to control.  I am not using an "all" here, as i thought it would be over kill, but it would be easy to adapt. "r","g","b"; these are the colors to use.  I am using 0-255 to control the colors, so each Red, Green, Blue value gets mapped.  I have it doubled up, as some patterns require two colors.  
