static void show_datestring(const char *flag, const char *datestr)
{
	char *buffer;

	/* date handling requires both flags and revs */
	if ((filter & (DO_FLAGS | DO_REVS)) != (DO_FLAGS | DO_REVS))
		return;
	buffer = xstrfmt("%s%"PRItime, flag, approxidate(datestr));
	show(buffer);
	free(buffer);
}