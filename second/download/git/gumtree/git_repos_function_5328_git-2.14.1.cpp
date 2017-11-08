static const char *branch_get_color(enum color_branch ix)
{
	if (want_color(branch_use_color))
		return branch_colors[ix];
	return "";
}