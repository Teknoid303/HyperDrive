# HyperDrive

Flite Test is doing a build video on the HyperDrive that Jesse Perkins and I built for their Whoop Course at Edgewater Airpark. This GitHub is in support of that video.

# Electronics Build
**Electronic Parts** - One of each of the items listed below. 
- Arduino Nano
- WS2812B LED Strips (length and quantity depends on the size of your gate)
- Resistor (220-470 ohm) - Optional but suggested
- Various Wire

The connections are fairly simple and can be repeated for as many LED strands you want in your gate.
# ![Schematic](media/HyperDriveCircuit.jpg)

## IMPORTANT - Power Supply Selection
You will need a 5v power supply for this gate. The type and rating of the power supply you select depends on the **TOTAL** number of LEDs that will be in your gate. As a rule of thumb, and only for this display pattern, you will need about 4W of power at 5v for every 120 LEDs you are running. The 8 foot gate at Flite Test used nearly 900 LEDs, which required a 30 watt power supply. Generally, I go double on my supplies because I know I will change the pattern at some point and push it further.

# Programming
Included here is a very simple code that will be uploaded to each Nano/LED Strip you have to create the feeling of "Hitting the HyperDrive" and "Flying Through a Starfield". It creates a "star" 7 LEDs long (**LEAD_LEDS**), that fade from the first to the last, traveling at speeds varying between **MIN_STAR_SPEED** and **MAX_STAR_SPEED** down the length of the strand. There can be multiple stars traveling on each strand, controlled by **STARS_PER_STRAND**, that will overtake others if they are traveling faster.

**Number of LEDs** - When installing the LEDs on your HyperDrive, the number of LEDs may differ from those we used on the one at Flite Test, so be sure and count your LEDs and change the following line as needed:

#define NUM_LEDS         147

**Brightness** - Your hyperdrive may be in a dark room, which will require the dimming of the LEDs so that they don't become blinding to the FPV camera. Reduce the number below to your liking. The number runs from 0-255, with 255 being the brightest. 63 is 1/4 brightness, 127 is 1/2, and 191 is 3/4.

#define INIT_BRIGHTNESS   255

