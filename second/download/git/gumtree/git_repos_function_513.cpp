static int git_default_branch_config(const char *var, const char *value)
{
	if (!strcmp(var, "branch.autosetupmerge")) {
		if (value && !strcasecmp(value, "always")) {
			git_branch_track = BRANCH_TRACK_ALWAYS;
			return 0;
		}
		git_branch_track = git_config_bool(var, value);
		return 0;
	}
	if (!strcmp(var, "branch.autosetuprebase")) {
		if (!value)
			return config_error_nonbool(var);
		else if (!strcmp(value, "never"))
			autorebase = AUTOREBASE_NEVER;
		else if (!strcmp(value, "local"))
			autorebase = AUTOREBASE_LOCAL;
		else if (!strcmp(value, "remote"))
			autorebase = AUTOREBASE_REMOTE;
		else if (!strcmp(value, "always"))
			autorebase = AUTOREBASE_ALWAYS;
		else
			return error("Malformed value for %s", var);
		return 0;
	}

	/* Add other config variables here and to Documentation/config.txt. */
	return 0;
}