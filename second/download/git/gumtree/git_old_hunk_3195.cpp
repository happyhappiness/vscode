	ret = git_configset_get_pathname(&the_config_set, key, dest);
	if (ret < 0)
		git_die_config(key, NULL);
	return ret;
}

NORETURN
void git_die_config_linenr(const char *key, const char *filename, int linenr)
{
	if (!filename)
		die(_("unable to parse '%s' from command-line config"), key);
	else
