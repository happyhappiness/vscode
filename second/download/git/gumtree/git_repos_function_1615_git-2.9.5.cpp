static int is_date(int year, int month, int day, struct tm *now_tm, time_t now, struct tm *tm)
{
	if (month > 0 && month < 13 && day > 0 && day < 32) {
		struct tm check = *tm;
		struct tm *r = (now_tm ? &check : tm);
		time_t specified;

		r->tm_mon = month - 1;
		r->tm_mday = day;
		if (year == -1) {
			if (!now_tm)
				return 1;
			r->tm_year = now_tm->tm_year;
		}
		else if (year >= 1970 && year < 2100)
			r->tm_year = year - 1900;
		else if (year > 70 && year < 100)
			r->tm_year = year;
		else if (year < 38)
			r->tm_year = year + 100;
		else
			return 0;
		if (!now_tm)
			return 1;

		specified = tm_to_time_t(r);

		/* Be it commit time or author time, it does not make
		 * sense to specify timestamp way into the future.  Make
		 * sure it is not later than ten days from now...
		 */
		if ((specified != -1) && (now + 10*24*3600 < specified))
			return 0;
		tm->tm_mon = r->tm_mon;
		tm->tm_mday = r->tm_mday;
		if (year != -1)
			tm->tm_year = r->tm_year;
		return 1;
	}
	return 0;
}