static const char *clean_get_color(enum color_clean ix)
{
	if (want_color(clean_use_color))
		return clean_colors[ix];
	return "";
}