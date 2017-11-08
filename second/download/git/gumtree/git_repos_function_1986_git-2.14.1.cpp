static int local_tzoffset(timestamp_t time)
{
	time_t t, t_local;
	struct tm tm;
	int offset, eastwest;

	if (date_overflows(time))
		die("Timestamp too large for this system: %"PRItime, time);

	t = (time_t)time;
	localtime_r(&t, &tm);
	t_local = tm_to_time_t(&tm);

	if (t_local == -1)
		return 0; /* error; just use +0000 */
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