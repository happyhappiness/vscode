static int check_auto_color(void)
{
	if (color_stdout_is_tty < 0)
		color_stdout_is_tty = isatty(1);
	if (color_stdout_is_tty || (pager_in_use() && pager_use_color)) {
		char *term = getenv("TERM");
		if (term && strcmp(term, "dumb"))
			return 1;
	}
	return 0;
}