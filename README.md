  btn-watch
=======

Simple user app to demonstrate monitoring the Overo expansion card buttons.

There are make files for cross-builds using an OE environment (Gumstix specific)
and for doing native builds on the Overo.

	$ git clone git://github.com/scottellis/btn-watch.git
	$ cd btn-watch
	$ make
	/oe4/sysroots/`uname -m`-linux/usr/armv7a/bin/arm-angstrom-linux-gnueabi-gcc -Wall -I /oe4/sysroots/armv7a-angstrom-linux-gnueabi/usr/include -L /oe4/sysroots/armv7a-angstrom-linux-gnueabi/usr/lib btn-watch.c -o btn-watch

Or if you have your OE TMPDIR pointing somewhere else

	$ OETMP=/oe4 make
	/oe4/sysroots/`uname -m`-linux/usr/armv7a/bin/arm-angstrom-linux-gnueabi-gcc -Wall -I /oe4/sysroots/armv7a-angstrom-linux-gnueabi/usr/include -L /oe4/sysroots/armv7a-angstrom-linux-gnueabi/usr/lib btn-watch.c -o btn-watch

Then copy the btn-watch executable to your Gumstix however is convenient.

If you want to compile the code on your Overo, use the Makefile-native make file.

	root@overo:~/btn-watch# make -f Makefile-native 
	gcc -Wall btn-watch.c -o btn-watch

And here is what it looks like running and then pressing each of the buttons a few times.

	root@overo:~/btn-watch# ./btn-watch
	btn_0 (GPIO14) code 256
	btn_1 (GPIO21) code 257
	Watching 2 buttons (ctrl-C to exit)
	btn_1: 0
	btn_1: 1
	btn_1: 0
	btn_1: 1
	btn_1: 0
	btn_1: 1
	btn_0: 0
	btn_0: 1
	btn_0: 0
	btn_0: 1
	btn_0: 0
	btn_0: 1
	btn_0: 0
	btn_0: 1

