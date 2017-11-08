static void output_sep(struct grep_opt *opt, char sign)
{
	if (opt->null_following_name)
		opt->output(opt, "\0", 1);
	else
		output_color(opt, &sign, 1, opt->color_sep);
}