#include "rock5_pwm.h"

#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    int channel = 1;
    float frequency = 100; // Hz
    if (argc > 1) {
	channel = atoi(argv[1]);
    }
    printf("Enabling PWM on channel %d.\n",channel);
    PWM pwm;
    try {
	pwm.start(channel, frequency);
    } catch (std::invalid_argument const& ex) {
	std::cout << ex.what() << std::endl;
	return -1;
    }
    printf("Duty cycle at 50%%. Press <enter>.\n");
    pwm.setDutyCycle(50);
    getchar();
    printf("Duty cycle at 25%%. Press <enter>\n");
    pwm.setDutyCycle(25);
    getchar();
    printf("Duty cycle at 75%%. Press <enter>\n");
    pwm.setDutyCycle(75);
    getchar();
    printf("Disabling PWM on channel %d.\n",channel);
    pwm.stop();
    return 0;
}
