int parse_expiry_date(const char *date, unsigned long *timestamp)
{
	int errors = 0;

	if (!strcmp(date, "never") || !strcmp(date, "false"))
		*timestamp = 0;
	else if (!strcmp(date, "all") || !strcmp(date, "now"))
		/*
		 * We take over "now" here, which usually translates
		 * to the current timestamp.  This is because the user
		 * really means to expire everything she has done in
		 * the past, and by definition reflogs are the record
		 * of the past, and there is nothing from the future
		 * to be kept.
		 */
		*timestamp = ULONG_MAX;
	else
		*timestamp = approxidate_careful(date, &errors);

	return errors;
}