static const char *config_get_ff(void)
{
	const char *value;

	if (git_config_get_value("pull.ff", &value))
		return NULL;

	switch (git_config_maybe_bool("pull.ff", value)) {
	case 0:
		return "--no-ff";
	case 1:
		return "--ff";
	}

	if (!strcmp(value, "only"))
		return "--ff-only";

	die(_("Invalid value for pull.ff: %s"), value);
}