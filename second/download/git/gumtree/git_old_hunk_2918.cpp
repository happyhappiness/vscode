struct date_mode *date_mode_from_type(enum date_mode_type type)
{
	static struct date_mode mode;
	if (type == DATE_STRFTIME)
		die("BUG: cannot create anonymous strftime date_mode struct");
	mode.type = type;
	return &mode;
}

const char *show_date(unsigned long time, int tz, const struct date_mode *mode)
{
	struct tm *tm;
	static struct strbuf timebuf = STRBUF_INIT;

	if (mode->type == DATE_RAW) {
		strbuf_reset(&timebuf);
		strbuf_addf(&timebuf, "%lu %+05d", time, tz);
		return timebuf.buf;
	}

