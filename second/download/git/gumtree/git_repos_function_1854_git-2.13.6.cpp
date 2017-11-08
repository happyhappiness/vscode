int want_color(int var)
{
	static int want_auto = -1;

	if (var < 0)
		var = git_use_color_default;

	if (var == GIT_COLOR_AUTO) {
		if (want_auto < 0)
			want_auto = check_auto_color();
		return want_auto;
	}
	return var;
}