static int parse_reedit_arg(const struct option *opt, const char *arg, int unset)
{
	struct note_data *d = opt->value;
	d->use_editor = 1;
	return parse_reuse_arg(opt, arg, unset);
}