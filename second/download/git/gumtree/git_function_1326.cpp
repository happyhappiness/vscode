static time_t gm_time_t(timestamp_t time, int tz)
{
	int minutes;

	minutes = tz < 0 ? -tz : tz;
	minutes = (minutes / 100)*60 + (minutes % 100);
	minutes = tz < 0 ? -minutes : minutes;

	if (minutes > 0) {
		if (unsigned_add_overflows(time, minutes * 60))
			die("Timestamp+tz too large: %"PRItime" +%04d",
			    time, tz);
	} else if (time < -minutes * 60)
		die("Timestamp before Unix epoch: %"PRItime" %04d", time, tz);
	time += minutes * 60;
	if (date_overflows(time))
		die("Timestamp too large for this system: %"PRItime, time);
	return (time_t)time;
}