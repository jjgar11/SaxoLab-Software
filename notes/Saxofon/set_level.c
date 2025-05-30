#include <stdio.h>
#include <stdlib.h>
#include <lo/lo.h>
#include <unistd.h>
#define OSC_PORT 5513
int main() {
	lo_address t = lo_address_new("localhost", "5513");
	double level;
	level = 0.01 ;
	for (int i = 0; i < 10; i++) {
		lo_send(t, "/noise/level", "f", level);
		printf("Aumentando Nivel de volúmen a %f\n", level);
		level += 0.1;
		usleep(500000);
	}
	return 0;
}
