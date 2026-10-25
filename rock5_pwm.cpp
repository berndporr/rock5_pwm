#include "rock5_pwm.h"

int PWM::start(int channel, float frequency)
{
    chippath = "/sys/class/pwm/pwmchip" + std::to_string(channel);
	pwmpath = chippath + "/pwm0";
	std::string p = chippath + "/export";
	FILE *const fp = fopen(p.c_str(), "w");
	if (NULL == fp)
	{
		fprintf(stderr, "PWM device: chip %d does not exist.\n", channel);
		return -1;
	}
	for (int i = 0;; i++)
	{
		const int r = fprintf(fp, "0");
		fflush(fp);
		if (r > 0)
			break;
		if (i > export_attempts)
		{
			std::cerr << "Timeout exporting:" << p << std::endl;
			return -1;
		}
		usleep(retry_delay_us);
	}
	fclose(fp);
	int r;
	for (int i = 0;; i++)
	{
		r = enable();
		if (r > 0)
			break;
		usleep(retry_delay_us);
		if (i > export_attempts)
		{
			std::cerr << "Timeout enabling:" << pwmpath << std::endl;
			return -1;
		}
	}
	r = setPeriodNS((int)(1E9/frequency));
	if (r < 0)
	{
		std::cerr << "Could not set period during startup of PWM: " << pwmpath << std::endl;
		return r;
	}
	return r;
}
