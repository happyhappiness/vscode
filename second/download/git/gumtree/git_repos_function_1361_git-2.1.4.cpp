static int match_digit(const char *date, struct tm *tm, int *offset, int *tm_gmt)
{
	int n;
	char *end;
	unsigned long num;

	num = strtoul(date, &end, 10);

	/*
	 * Seconds since 1970? We trigger on that for any numbers with
	 * more than 8 digits. This is because we don't want to rule out
	 * numbers like 20070606 as a YYYYMMDD date.
	 */
	if (num >= 100000000 && nodate(tm)) {
		time_t time = num;
		if (gmtime_r(&time, tm)) {
			*tm_gmt = 1;
			return end - date;
		}
	}

	/*
	 * Check for special formats: num[-.:/]num[same]num
	 */
	switch (*end) {
	case ':':
	case '.':
	case '/':
	case '-':
		if (isdigit(end[1])) {
			int match = match_multi_number(num, *end, date, end, tm);
			if (match)
				return match;
		}
	}

	/*
	 * None of the special formats? Try to guess what
	 * the number meant. We use the number of digits
	 * to make a more educated guess..
	 */
	n = 0;
	do {
		n++;
	} while (isdigit(date[n]));

	/* Four-digit year or a timezone? */
	if (n == 4) {
		if (num <= 1400 && *offset == -1) {
			unsigned int minutes = num % 100;
			unsigned int hours = num / 100;
			*offset = hours*60 + minutes;
		} else if (num > 1900 && num < 2100)
			tm->tm_year = num - 1900;
		return n;
	}

	/*
	 * Ignore lots of numerals. We took care of 4-digit years above.
	 * Days or months must be one or two digits.
	 */
	if (n > 2)
		return n;

	/*
	 * NOTE! We will give precedence to day-of-month over month or
	 * year numbers in the 1-12 range. So 05 is always "mday 5",
	 * unless we already have a mday..
	 *
	 * IOW, 01 Apr 05 parses as "April 1st, 2005".
	 */
	if (num > 0 && num < 32 && tm->tm_mday < 0) {
		tm->tm_mday = num;
		return n;
	}

	/* Two-digit year? */
	if (n == 2 && tm->tm_year < 0) {
		if (num < 10 && tm->tm_mday >= 0) {
			tm->tm_year = num + 100;
			return n;
		}
		if (num >= 70) {
			tm->tm_year = num;
			return n;
		}
	}

	if (num > 0 && num < 13 && tm->tm_mon < 0)
		tm->tm_mon = num-1;

	return n;
}