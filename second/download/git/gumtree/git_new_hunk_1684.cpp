		if (git_config_parse_parameter(config->items[i].string,
					       write_one_config, NULL) < 0)
			die("unable to write parameters to config file");
	}
}

static void write_refspec_config(const char *src_ref_prefix,
		const struct ref *our_head_points_at,
		const struct ref *remote_head_points_at,
		struct strbuf *branch_top)
{
	struct strbuf key = STRBUF_INIT;
	struct strbuf value = STRBUF_INIT;

	if (option_mirror || !option_bare) {
		if (option_single_branch && !option_mirror) {
