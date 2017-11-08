static void finish_up_to_date(const char *msg)
{
	if (verbosity >= 0)
		printf("%s%s\n", squash ? _(" (nothing to squash)") : "", msg);
	drop_save();
}