int date_overflows(timestamp_t t)
{
	time_t sys;

	/* If we overflowed our timestamp data type, that's bad... */
	if ((uintmax_t)t >= TIME_MAX)
		return 1;

	/*
	 * ...but we also are going to feed the result to system
	 * functions that expect time_t, which is often "signed long".
	 * Make sure that we fit into time_t, as well.
	 */
	sys = t;
	return t != sys || (t < 1) != (sys < 1);
}