static int local_tzoffset(unsigned long time)
{
	time_t t, t_local;
	struct tm tm;
	int offset, eastwest;

	t = time;
	localtime_r(&t, &tm);
	t_local = tm_to_time_t(&tm);

	if (t_local < t) {
		eastwest = -1;
		offset = t - t_local;
	} else {
		eastwest = 1;
		offset = t_local - t;
	}
	offset /= 60; /* in minutes */
	offset = (offset % 60) + ((offset / 60) * 100);
	return offset * eastwest;
}