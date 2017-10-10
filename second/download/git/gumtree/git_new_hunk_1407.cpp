};

static const char *weekday_names[] = {
	"Sundays", "Mondays", "Tuesdays", "Wednesdays", "Thursdays", "Fridays", "Saturdays"
};

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

/*
 * The "tz" thing is passed in as this strange "decimal parse of tz"
 * thing, which means that tz -0100 is passed in as the integer -100,
 * even though it means "sixty minutes off"
 */
static struct tm *time_to_tm(timestamp_t time, int tz)
{
	time_t t = gm_time_t(time, tz);
	return gmtime(&t);
}

static struct tm *time_to_tm_local(timestamp_t time)
{
	time_t t = time;
	return localtime(&t);
}

/*
 * What value of "tz" was in effect back then at "time" in the
 * local timezone?
 */
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
