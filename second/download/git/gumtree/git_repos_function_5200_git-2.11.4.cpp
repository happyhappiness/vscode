static const char *get_color_reset_code(void)
{
	if (want_color(showbranch_use_color))
		return GIT_COLOR_RESET;
	return "";
}