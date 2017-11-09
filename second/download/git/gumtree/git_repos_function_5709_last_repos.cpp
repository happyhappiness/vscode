static int no_numbered_callback(const struct option *opt, const char *arg,
				int unset)
{
	return numbered_callback(opt, arg, 1);
}