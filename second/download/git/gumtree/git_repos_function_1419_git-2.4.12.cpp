const char *show_date(unsigned long time, int tz, enum date_mode mode)
{
	struct tm *tm;
	static struct strbuf timebuf = STRBUF_INIT;

	if (mode == DATE_RAW) {
		strbuf_reset(&timebuf);
		strbuf_addf(&timebuf, "%lu %+05d", time, tz);
		return timebuf.buf;
	}

	if (mode == DATE_RELATIVE) {
		struct timeval now;

		strbuf_reset(&timebuf);
		gettimeofday(&now, NULL);
		show_date_relative(time, tz, &now, &timebuf);
		return timebuf.buf;
	}

	if (mode == DATE_LOCAL)
		tz = local_tzoffset(time);

	tm = time_to_tm(time, tz);
	if (!tm) {
		tm = time_to_tm(0, 0);
		tz = 0;
	}

	strbuf_reset(&timebuf);
	if (mode == DATE_SHORT)
		strbuf_addf(&timebuf, "%04d-%02d-%02d", tm->tm_year + 1900,
				tm->tm_mon + 1, tm->tm_mday);
	else if (mode == DATE_ISO8601)
		strbuf_addf(&timebuf, "%04d-%02d-%02d %02d:%02d:%02d %+05d",
				tm->tm_year + 1900,
				tm->tm_mon + 1,
				tm->tm_mday,
				tm->tm_hour, tm->tm_min, tm->tm_sec,
				tz);
	else if (mode == DATE_ISO8601_STRICT) {
		char sign = (tz >= 0) ? '+' : '-';
		tz = abs(tz);
		strbuf_addf(&timebuf, "%04d-%02d-%02dT%02d:%02d:%02d%c%02d:%02d",
				tm->tm_year + 1900,
				tm->tm_mon + 1,
				tm->tm_mday,
				tm->tm_hour, tm->tm_min, tm->tm_sec,
				sign, tz / 100, tz % 100);
	} else if (mode == DATE_RFC2822)
		strbuf_addf(&timebuf, "%.3s, %d %.3s %d %02d:%02d:%02d %+05d",
			weekday_names[tm->tm_wday], tm->tm_mday,
			month_names[tm->tm_mon], tm->tm_year + 1900,
			tm->tm_hour, tm->tm_min, tm->tm_sec, tz);
	else
		strbuf_addf(&timebuf, "%.3s %.3s %d %02d:%02d:%02d %d%c%+05d",
				weekday_names[tm->tm_wday],
				month_names[tm->tm_mon],
				tm->tm_mday,
				tm->tm_hour, tm->tm_min, tm->tm_sec,
				tm->tm_year + 1900,
				(mode == DATE_LOCAL) ? 0 : ' ',
				tz);
	return timebuf.buf;
}