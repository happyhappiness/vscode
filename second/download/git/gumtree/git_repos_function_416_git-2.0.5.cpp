NORETURN
static void die_bad_number(const char *name, const char *value)
{
	const char *reason = errno == ERANGE ?
			     "out of range" :
			     "invalid unit";
	if (!value)
		value = "";

	if (cf && cf->name)
		die("bad numeric config value '%s' for '%s' in %s: %s",
		    value, name, cf->name, reason);
	die("bad numeric config value '%s' for '%s': %s", value, name, reason);
}