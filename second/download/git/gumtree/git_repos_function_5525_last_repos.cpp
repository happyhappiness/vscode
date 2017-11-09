static const char *get_color_code(int idx)
{
	if (want_color(showbranch_use_color))
		return column_colors_ansi[idx % column_colors_ansi_max];
	return "";
}