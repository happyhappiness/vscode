static int really_refresh_callback(const struct option *opt,
				const char *arg, int unset)
{
	return refresh(opt->value, REFRESH_REALLY);
}