static int parse_force_date(const char *in, char *out, int len)
{
	if (len < 1)
		return -1;
	*out++ = '@';
	len--;

	if (parse_date(in, out, len) < 0) {
		int errors = 0;
		unsigned long t = approxidate_careful(in, &errors);
		if (errors)
			return -1;
		snprintf(out, len, "%lu", t);
	}

	return 0;
}