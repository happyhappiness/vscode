static const char *decorate_get_color(int decorate_use_color, enum decoration_type ix)
{
	if (want_color(decorate_use_color))
		return decoration_colors[ix];
	return "";
}