char *do_big_dnum(double dnum, int human_flag, int decimal_digits)
{
	static char tmp_buf[128];
#if SIZEOF_INT64 >= 8
	char *fract;

	snprintf(tmp_buf, sizeof tmp_buf, "%.*f", decimal_digits, dnum);

	if (!human_flag || (dnum < 1000.0 && dnum > -1000.0))
		return tmp_buf;

	for (fract = tmp_buf+1; isDigit(fract); fract++) {}

	return do_big_num((int64)dnum, human_flag, fract);
#else
	/* A big number might lose digits converting to a too-short int64,
	 * so let's just return the raw double conversion. */
	snprintf(tmp_buf, sizeof tmp_buf, "%.*f", decimal_digits, dnum);
	return tmp_buf;
#endif
}