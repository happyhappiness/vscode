static const char *approxidate_digit(const char *date, struct tm *tm, int *num)
{
	char *end;
	unsigned long number = strtoul(date, &end, 10);

	switch (*end) {
	case ':':
	case '.':
	case '/':
	case '-':
		if (isdigit(end[1])) {
			int match = match_multi_number(number, *end, date, end, tm);
			if (match)
				return date + match;
		}
	}

	/* Accept zero-padding only for small numbers ("Dec 02", never "Dec 0002") */
	if (date[0] != '0' || end - date <= 2)
		*num = number;
	return end;
}