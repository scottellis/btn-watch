/*
 * Example to monitor the gpio buttons on an Overo expansion board.
 */

#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <fcntl.h>
#include <unistd.h>

#include <linux/input.h>

/* macros taken from evtest.c http://cgit.freedesktop.org/~whot/evtest/ */
#define BITS_PER_LONG (sizeof(long) * 8)
#define NBITS(x) ((((x)-1)/BITS_PER_LONG)+1)
#define OFF(x)  ((x)%BITS_PER_LONG)
#define BIT(x)  (1UL<<OFF(x))
#define LONG(x) ((x)/BITS_PER_LONG)
#define test_bit(bit, array)	((array[LONG(bit)] >> OFF(bit)) & 1)


int watch_events(int fd, int num_buttons)
{
	int size, len, i;
	struct input_event *events;
	size = sizeof(struct input_event) * num_buttons * 4;

	events = malloc(size);

	if (!events)
		return -1;

	while (1) {
		memset(events, 0, size);
		
		len = read(fd, events, size);

		if (len < sizeof(struct input_event))
			break;

		len /= sizeof(struct input_event);

		for (i = 0; i < len; i++) {
			if (events[i].type == EV_KEY) {
				if (events[i].code == BTN_0)
					printf("btn_0: %d\n", events[i].value);
				else if (events[i].code == BTN_1)
					printf("btn_1: %d\n", events[i].value);
				else 
					printf("btn[%u]: %d\n",
						events[i].code, events[i].value);
			}
		}
	}

	free(events);

	return len;
}

int main(int argc, char **argv)
{
	int fd, i, num_buttons;
	unsigned long buttons[NBITS(KEY_MAX)];

	fd = open("/dev/input/by-path/platform-gpio-keys-event", O_RDONLY);

	if (fd < 0) {
		perror("open");
		return 1;
	}
		
	memset(buttons, 0, sizeof(buttons));

	if (ioctl(fd, EVIOCGBIT(EV_KEY, KEY_MAX), buttons) < 0) {
		perror("EVIOCGBIT(EV_KEY, KEY_MAX)");
		goto done;
	}

	num_buttons = 0;

	for (i = 0; i < KEY_MAX; i++) {
		if (test_bit(i, buttons)) {
			if (i == BTN_0)
				printf("btn_0 (GPIO14) code %d\n", i);
			else if (i == BTN_1)
				printf("btn_1 (GPIO21) code %d\n", i);
			else
				printf("Unknown button code %d\n", i);

			num_buttons++;
		}
	}

	printf("Watching %d buttons (ctrl-C to exit)\n", num_buttons);

	watch_events(fd, num_buttons);
		
done:

	close(fd);

	return 0;
}

