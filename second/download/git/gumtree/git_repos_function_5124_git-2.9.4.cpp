static int parse_decoration_style(const char *var, const char *value)
{
	switch (git_config_maybe_bool(var, value)) {
	case 1:
		return DECORATE_SHORT_REFS;
	case 0:
		return 0;
	default:
		break;
	}
	if (!strcmp(value, "full"))
		return DECORATE_FULL_REFS;
	else if (!strcmp(value, "short"))
		return DECORATE_SHORT_REFS;
	else if (!strcmp(value, "auto"))
		return (isatty(1) || pager_in_use()) ? DECORATE_SHORT_REFS : 0;
	return -1;
}