static void output_color(struct grep_opt *opt, const void *data, size_t size,
			 const char *color)
{
	if (want_color(opt->color) && color && color[0]) {
		opt->output(opt, color, strlen(color));
		opt->output(opt, data, size);
		opt->output(opt, GIT_COLOR_RESET, strlen(GIT_COLOR_RESET));
	} else
		opt->output(opt, data, size);
}