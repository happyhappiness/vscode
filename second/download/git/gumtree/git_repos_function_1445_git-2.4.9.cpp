static const char *approxidate_alpha(const char *date, struct tm *tm, struct tm *now, int *num, int *touched)
{
	const struct typelen *tl;
	const struct special *s;
	const char *end = date;
	int i;

	while (isalpha(*++end))
		;

	for (i = 0; i < 12; i++) {
		int match = match_string(date, month_names[i]);
		if (match >= 3) {
			tm->tm_mon = i;
			*touched = 1;
			return end;
		}
	}

	for (s = special; s->name; s++) {
		int len = strlen(s->name);
		if (match_string(date, s->name) == len) {
			s->fn(tm, now, num);
			*touched = 1;
			return end;
		}
	}

	if (!*num) {
		for (i = 1; i < 11; i++) {
			int len = strlen(number_name[i]);
			if (match_string(date, number_name[i]) == len) {
				*num = i;
				*touched = 1;
				return end;
			}
		}
		if (match_string(date, "last") == 4) {
			*num = 1;
			*touched = 1;
		}
		return end;
	}

	tl = typelen;
	while (tl->type) {
		int len = strlen(tl->type);
		if (match_string(date, tl->type) >= len-1) {
			update_tm(tm, now, tl->length * *num);
			*num = 0;
			*touched = 1;
			return end;
		}
		tl++;
	}

	for (i = 0; i < 7; i++) {
		int match = match_string(date, weekday_names[i]);
		if (match >= 3) {
			int diff, n = *num -1;
			*num = 0;

			diff = tm->tm_wday - i;
			if (diff <= 0)
				n++;
			diff += 7*n;

			update_tm(tm, now, diff * 24 * 60 * 60);
			*touched = 1;
			return end;
		}
	}

	if (match_string(date, "months") >= 5) {
		int n;
		update_tm(tm, now, 0); /* fill in date fields if needed */
		n = tm->tm_mon - *num;
		*num = 0;
		while (n < 0) {
			n += 12;
			tm->tm_year--;
		}
		tm->tm_mon = n;
		*touched = 1;
		return end;
	}

	if (match_string(date, "years") >= 4) {
		update_tm(tm, now, 0); /* fill in date fields if needed */
		tm->tm_year -= *num;
		*num = 0;
		*touched = 1;
		return end;
	}

	return end;
}