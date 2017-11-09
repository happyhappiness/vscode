static int refresh_callback(const struct option *opt,
				const char *arg, int unset)
{
	return refresh(opt->value, 0);
}