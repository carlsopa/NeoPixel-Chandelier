# NeoPixel-Chandelier
Apartments are a hard place to live in at times, as they may not always be the best lit. Such is the case of my apartment’s living room. So I set out to fix that, thus the chandelier was born. I was looking for an item that would work easily with my existing home network, be easy to control, brighten the room and look cool.

The design is something that I have been toying with for quite a while. There is just something pleasing and appealing about the older-fashioned glass bottles. So when I was cleaning out an area in a store recently I came across several old bottles and some older wood. Combining both of these together, I finally saw my dream become reality. I had the bottles cleaned up, and the wood distressed to give it a little more aged look.

The chandelier is using Several Adafruit Neopixels to light up multiple layers.  It is using the following:<ul>
<li>2x- Neopixel strips</li>
<li>4x- Neopixel quarter ring</li>
<li>6x- Individual neopixels hooked in sequence</li>
<li>1x- Individual neopixel</li>
</ul>

The lighting design has two strips running around the top outside portion. These can be controlled together to give it a unique full look. My 4 quarter pieces make up a full circle which is connected underneath the chandelier, wrapping around a center bottle. I have 6 bottles that go around the outside of the design, and then one final central bottle. Each bottle has its own individual Neopixel. The 6 outside are connected in sequence, and the central bottle is left separate.

The whole setup is controlled by an Adafruit ESP8266 Feather. Commands are received as MQTT messages on a single thread, and the payload is broken apart to determine the actual action. I am using a 9v power supply to supply energy to the whole piece.

As mentioned, it is using MQTT topics and payload for control. It has a current topic that it is subscribed to, and when a payload is published on said topic it will break it apart to control the lights. I have it written where it needs to be done in a specific fashion, or else it could cause unwanted results. Two different types of payloads are also required. One lets you turn it on and off; the other is for animations.

paylod for control:
c:on/off:all/pin<br>
the "c" tells it that it will be a control message. "on"/"off" tell it what to do, and the "all" or "pin" tell it what lights to work with. If you give it a number for pin, then it will be that specific set. If you use “all”, it will be all the lights at once.

a:pattern:pin:r:g: b :r:g:b <br>
The "a" tells us that it will be patterned. I have setup some specific patterns that use a shortened version that we will send using the payload. The "pattern" tells the program what to show. "pin" is linked to a specific set of lights to control. I am not using an "all" here, as I thought it would be overkill, but it would be easy to adapt. "r","g","b"; these are the colors to use. I am using 0-255 to control the colors, so each Red, Green, Blue value gets mapped. I have it doubled up, as some patterns require two colors.

View demonstration of the chandelier: <a href="https://www.youtube.com/watch?time_continue=2&v=eSuQJpV_RyI">Recycled Chandelier</a>
