NORETURN
static void die_bad_number(const char *name, const char *value)
{
	const char * error_type = (errno == ERANGE)? _("out of range"):_("invalid unit");

	if (!value)
		value = "";

	if (!(cf && cf->name))
		die(_("bad numeric config value '%s' for '%s': %s"),
		    value, name, error_type);

	switch (cf->origin_type) {
	case CONFIG_ORIGIN_BLOB:
		die(_("bad numeric config value '%s' for '%s' in blob %s: %s"),
		    value, name, cf->name, error_type);
	case CONFIG_ORIGIN_FILE:
		die(_("bad numeric config value '%s' for '%s' in file %s: %s"),
		    value, name, cf->name, error_type);
	case CONFIG_ORIGIN_STDIN:
		die(_("bad numeric config value '%s' for '%s' in standard input: %s"),
		    value, name, error_type);
	case CONFIG_ORIGIN_SUBMODULE_BLOB:
		die(_("bad numeric config value '%s' for '%s' in submodule-blob %s: %s"),
		    value, name, cf->name, error_type);
	case CONFIG_ORIGIN_CMDLINE:
		die(_("bad numeric config value '%s' for '%s' in command line %s: %s"),
		    value, name, cf->name, error_type);
	default:
		die(_("bad numeric config value '%s' for '%s' in %s: %s"),
		    value, name, cf->name, error_type);
	}
}