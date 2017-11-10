static enum rebase_type parse_config_rebase(const char *key, const char *value,
		int fatal)
{
	int v = git_config_maybe_bool("pull.rebase", value);

	if (!v)
		return REBASE_FALSE;
	else if (v > 0)
		return REBASE_TRUE;
	else if (!strcmp(value, "preserve"))
		return REBASE_PRESERVE;
	else if (!strcmp(value, "interactive"))
		return REBASE_INTERACTIVE;

	if (fatal)
		die(_("Invalid value for %s: %s"), key, value);
	else
		error(_("Invalid value for %s: %s"), key, value);

	return REBASE_INVALID;
}