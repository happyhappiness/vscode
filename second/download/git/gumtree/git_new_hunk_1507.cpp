	return 0;
}

int parse_opt_merge_filter(const struct option *opt, const char *arg, int unset)
{
	struct ref_filter *rf = opt->value;
	struct object_id oid;
	int no_merged = starts_with(opt->long_name, "no");

	if (rf->merge) {
		if (no_merged) {
			return opterror(opt, "is incompatible with --merged", 0);
		} else {
