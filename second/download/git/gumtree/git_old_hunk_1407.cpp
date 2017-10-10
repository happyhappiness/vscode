};

static const char *weekday_names[] = {
	"Sundays", "Mondays", "Tuesdays", "Wednesdays", "Thursdays", "Fridays", "Saturdays"
};

static time_t gm_time_t(unsigned long time, int tz)
{
	int minutes;

	minutes = tz < 0 ? -tz : tz;
	minutes = (minutes / 100)*60 + (minutes % 100);
	minutes = tz < 0 ? -minutes : minutes;
	return time + minutes * 60;
}

/*
 * The "tz" thing is passed in as this strange "decimal parse of tz"
 * thing, which means that tz -0100 is passed in as the integer -100,
 * even though it means "sixty minutes off"
 */
static struct tm *time_to_tm(unsigned long time, int tz)
{
	time_t t = gm_time_t(time, tz);
	return gmtime(&t);
}

/*
 * What value of "tz" was in effect back then at "time" in the
 * local timezone?
 */
static int local_tzoffset(unsigned long time)
{
	time_t t, t_local;
	struct tm tm;
	int offset, eastwest;

	t = time;
	localtime_r(&t, &tm);
	t_local = tm_to_time_t(&tm);

	if (t_local == -1)
		return 0; /* error; just use +0000 */
	if (t_local < t) {
