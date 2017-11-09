char *do_big_num(int64 num, int human_flag, const char *fract)
{
	static char bufs[4][128]; /* more than enough room */
	static unsigned int n;
	char *s;
	int len, negated;

	if (human_flag && !number_separator) {
		char buf[32];
		snprintf(buf, sizeof buf, "%f", 3.14);
		if (strchr(buf, '.') != NULL)
			number_separator = ',';
		else
			number_separator = '.';
	}

	n = (n + 1) % (sizeof bufs / sizeof bufs[0]);

	if (human_flag > 1) {
		if (human_flag == 2)
			HUMANIFY(1000);
		else
			HUMANIFY(1024);
	}

	s = bufs[n] + sizeof bufs[0] - 1;
	if (fract) {
		len = strlen(fract);
		s -= len;
		strlcpy(s, fract, len + 1);
	} else
		*s = '\0';

	len = 0;

	if (!num)
		*--s = '0';
	if (num < 0) {
		/* A maximum-size negated number can't fit as a positive,
		 * so do one digit in negated form to start us off. */
		*--s = (char)(-(num % 10)) + '0';
		num = -(num / 10);
		len++;
		negated = 1;
	} else
		negated = 0;

	while (num) {
		if (human_flag) {
			if (len == 3) {
				*--s = number_separator;
				len = 1;
			} else
				len++;
		}
		*--s = (char)(num % 10) + '0';
		num /= 10;
	}

	if (negated)
		*--s = '-';

	return s;
}