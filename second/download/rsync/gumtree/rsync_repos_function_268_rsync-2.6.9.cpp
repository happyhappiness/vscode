char *human_num(int64 num)
{
	static char bufs[4][128]; /* more than enough room */
	static unsigned int n;
	char *s;

	n = (n + 1) % (sizeof bufs / sizeof bufs[0]);

	if (human_readable) {
		char units = '\0';
		int mult = human_readable == 1 ? 1000 : 1024;
		double dnum = 0;
		if (num > mult*mult*mult) {
			dnum = (double)num / (mult*mult*mult);
			units = 'G';
		} else if (num > mult*mult) {
			dnum = (double)num / (mult*mult);
			units = 'M';
		} else if (num > mult) {
			dnum = (double)num / mult;
			units = 'K';
		}
		if (units) {
			snprintf(bufs[n], sizeof bufs[0], "%.2f%c", dnum, units);
			return bufs[n];
		}
	}

	s = bufs[n] + sizeof bufs[0] - 1;
	*s = '\0';

	if (!num)
		*--s = '0';
	while (num) {
		*--s = (num % 10) + '0';
		num /= 10;
	}
	return s;
}