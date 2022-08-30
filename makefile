upload:
	avrdude -c usbasp -p m88p -B8 -U flash:w:main.hex

clean:
	avrdude -c usbasp -p m88p -B8 -e
set_fuse_bits: 
	avrdude -c usbasp -p m88p  -U lfuse:w:0xe2:m -U hfuse:w:0xdf:m -U efuse:w:0xf9:m -B8 -e