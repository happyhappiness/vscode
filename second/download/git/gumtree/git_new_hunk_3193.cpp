	const char *reason = errno == ERANGE ?
			     "out of range" :
			     "invalid unit";
	if (!value)
		value = "";

	if (cf && cf->origin_type && cf->name)
		die(_("bad numeric config value '%s' for '%s' in %s %s: %s"),
		    value, name, cf->origin_type, cf->name, reason);
	die(_("bad numeric config value '%s' for '%s': %s"), value, name, reason);
}

int git_config_int(const char *name, const char *value)
{
	int ret;
