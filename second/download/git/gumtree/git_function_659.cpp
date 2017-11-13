int set_disambiguate_hint_config(const char *var, const char *value)
{
	static const struct {
		const char *name;
		disambiguate_hint_fn fn;
	} hints[] = {
		{ "none", NULL },
		{ "commit", disambiguate_commit_only },
		{ "committish", disambiguate_committish_only },
		{ "tree", disambiguate_tree_only },
		{ "treeish", disambiguate_treeish_only },
		{ "blob", disambiguate_blob_only }
	};
	int i;

	if (!value)
		return config_error_nonbool(var);

	for (i = 0; i < ARRAY_SIZE(hints); i++) {
		if (!strcasecmp(value, hints[i].name)) {
			default_disambiguate_hint = hints[i].fn;
			return 0;
		}
	}

	return error("unknown hint type for '%s': %s", var, value);
}