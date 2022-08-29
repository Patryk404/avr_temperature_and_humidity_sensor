upload:
	avrdude -c usbasp -p m88p -B8 -U flash:w:main.hex

clean:
	avrdude -c usbasp -p m88p -B8 -e