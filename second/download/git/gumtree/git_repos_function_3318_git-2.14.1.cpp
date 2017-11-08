static void dos_time(timestamp_t *timestamp, int *dos_date, int *dos_time)
{
	time_t time;
	struct tm *t;

	if (date_overflows(*timestamp))
		die("timestamp too large for this system: %"PRItime,
		    *timestamp);
	time = (time_t)*timestamp;
	t = localtime(&time);
	*timestamp = time;

	*dos_date = t->tm_mday + (t->tm_mon + 1) * 32 +
	            (t->tm_year + 1900 - 1980) * 512;
	*dos_time = t->tm_sec / 2 + t->tm_min * 32 + t->tm_hour * 2048;
}