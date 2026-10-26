#include "rock5_pwm.h"

void PWM::start(int channel, float frequency)
{
    if (channel < 1) {
	throw std::invalid_argument("Only channels > 0 allowed.");
    }
    chippath = "/sys/class/pwm/pwmchip" + std::to_string(channel);
    pwmpath = chippath + "/pwm0";
    std::string p = chippath + "/export";
    FILE *const fp = fopen(p.c_str(), "w");
    if (NULL == fp)
	{
	    throw std::runtime_error("PWM device: "+p+
				     " does not exist.");
	}
    for (int i = 0;; i++)
	{
	    const int r = fprintf(fp, "0");
	    fflush(fp);
	    usleep(retry_delay_us);
	    if (r > 0)
		break;
	    if (i > export_attempts)
		{
		    throw std::runtime_error("Timeout exporting: "+
					     p);
		}
	}
    fclose(fp);
    int r;
    for (int i = 0;; i++)
	{
	    r = enable();
	    usleep(retry_delay_us);
	    if (r > 0)
		break;
	    if (i > export_attempts)
		{
		    throw std::runtime_error("Timeout enabling: "+
					     p);
		}
	}
    r = setPeriodNS((int)(1E9/frequency));
    if (r < 0)
	{
	    throw std::runtime_error("Could not set period for: "+pwmpath);
	}
}
