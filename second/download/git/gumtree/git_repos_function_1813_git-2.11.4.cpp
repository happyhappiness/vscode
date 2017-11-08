static struct tm *time_to_tm(unsigned long time, int tz)
{
	time_t t = gm_time_t(time, tz);
	return gmtime(&t);
}