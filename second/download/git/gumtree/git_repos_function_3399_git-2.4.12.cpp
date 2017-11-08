static void show_name(struct grep_opt *opt, const char *name)
{
	output_color(opt, name, strlen(name), opt->color_filename);
	opt->output(opt, opt->null_following_name ? "\0" : "\n", 1);
}