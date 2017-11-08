char *human_num(int64 num)
{
	static char bufs[4][128]; /* more than enough room */
	static unsigned int n;
	char *s;
	int negated;

	n = (n + 1) % (sizeof bufs / sizeof bufs[0]);

	if (human_readable) {
		if (human_readable == 1)
			HUMANIFY(1000);
		else
			HUMANIFY(1024);
	}

	s = bufs[n] + sizeof bufs[0] - 1;
	*s = '\0';

	if (!num)
		*--s = '0';
	if (num < 0) {
		/* A maximum-size negated number can't fit as a positive,
		 * so do one digit in negated form to start us off. */
		*--s = (char)(-(num % 10)) + '0';
		num = -(num / 10);
		negated = 1;
	} else
		negated = 0;

	while (num) {
		*--s = (char)(num % 10) + '0';
		num /= 10;
	}

	if (negated)
		*--s = '-';

	return s;
}