NORETURN
void git_die_config_linenr(const char *key, const char *filename, int linenr)
{
	if (!filename)
		die(_("unable to parse '%s' from command-line config"), key);
	else
		die(_("bad config variable '%s' in file '%s' at line %d"),
		    key, filename, linenr);
}