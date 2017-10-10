			     "out of range" :
			     "invalid unit";
	if (!value)
		value = "";

	if (cf && cf->name)
		die(_("bad numeric config value '%s' for '%s' in %s: %s"),
		    value, name, cf->name, reason);
	die(_("bad numeric config value '%s' for '%s': %s"), value, name, reason);
}

int git_config_int(const char *name, const char *value)
{
	int ret;
	if (!git_parse_int(value, &ret))
