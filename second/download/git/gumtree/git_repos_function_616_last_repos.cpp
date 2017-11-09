int parse_opt_ref_sorting(const struct option *opt, const char *arg, int unset)
{
	if (!arg) /* should --no-sort void the list ? */
		return -1;
	parse_ref_sorting(opt->value, arg);
	return 0;
}