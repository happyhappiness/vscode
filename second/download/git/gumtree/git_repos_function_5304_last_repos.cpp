static int opt_with_value(const char *arg, const char *opt, const char **value)
{
	if (skip_prefix(arg, opt, &arg)) {
		if (!*arg) {
			*value = NULL;
			return 1;
		}
		if (*arg++ == '=') {
			*value = arg;
			return 1;
		}
	}
	return 0;
}