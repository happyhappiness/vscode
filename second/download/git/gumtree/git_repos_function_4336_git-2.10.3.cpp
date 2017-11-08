static enum rebase_type config_get_rebase(void)
{
	struct branch *curr_branch = branch_get("HEAD");
	const char *value;

	if (curr_branch) {
		char *key = xstrfmt("branch.%s.rebase", curr_branch->name);

		if (!git_config_get_value(key, &value)) {
			enum rebase_type ret = parse_config_rebase(key, value, 1);
			free(key);
			return ret;
		}

		free(key);
	}

	if (!git_config_get_value("pull.rebase", &value))
		return parse_config_rebase("pull.rebase", value, 1);

	return REBASE_FALSE;
}