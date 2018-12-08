# ASSIGNMENT then

*randomPlaygroundMemories* aims to create a conversation between the fabrication process of the object and the childhood of its users. Its surface is covered by sand, which is meant to be manipulated by the users as a call for nostalgia. When participants interact with the sand, they reveal parts of the mechanism, made of photocells on rotating gears, and leave a physical trace of this interaction with the piece for the next users to come. Through this manipulation, the light reaching the core of the machine uncovers sonic memories from the fabrication process of the machine. These sounds come from recordings of the laser cutter, the CNC machine, the saws and the drills used to build the whole structure. The piece is, therefore, a record of physical conversations, an attempt to connect the present with the past by preserving old states of interaction and combining them with new ones.



Technically, this piece uses seven photocells connected to a multiplexor that is feeding data to an Arduino. Each resistance is installed on a gear using a system of ball bearings in order for the rotation of the sensor to occur without entangling the wires. The varying amount of light reaching the photocells changes their resistance which triggers the playback of multiple buffers in Max/MSP. The amplitude, the length and the playback speed of each sound vary according to the amount of light on the photocells. When the Arduino detects variations on the photocells, it enables the motor connected to the gears which changes the internal configuration of the machine.

![randomPlaygroundMemories](https://github.com/sambourgault/CART360/blob/master/ASSIGNMENTS/ASSIGNMENT_THEN/rpm1.png)
