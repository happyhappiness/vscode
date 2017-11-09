static int auto_decoration_style(void)
{
	return (isatty(1) || pager_in_use()) ? DECORATE_SHORT_REFS : 0;
}