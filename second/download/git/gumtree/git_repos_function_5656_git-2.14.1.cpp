static void init_log_defaults(void)
{
	init_grep_defaults();
	init_diff_ui_defaults();

	decoration_style = auto_decoration_style();
}