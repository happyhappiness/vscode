static int parse_opt_tag_of_filtered_mode(const struct option *opt,
					  const char *arg, int unset)
{
	if (unset || !strcmp(arg, "abort"))
		tag_of_filtered_mode = ERROR;
	else if (!strcmp(arg, "drop"))
		tag_of_filtered_mode = DROP;
	else if (!strcmp(arg, "rewrite"))
		tag_of_filtered_mode = REWRITE;
	else
		return error("Unknown tag-of-filtered mode: %s", arg);
	return 0;
}