int parse_hide_refs_config(const char *var, const char *value, const char *section)
{
	const char *key;
	if (!strcmp("transfer.hiderefs", var) ||
	    (!parse_config_key(var, section, NULL, NULL, &key) &&
	     !strcmp(key, "hiderefs"))) {
		char *ref;
		int len;

		if (!value)
			return config_error_nonbool(var);
		ref = xstrdup(value);
		len = strlen(ref);
		while (len && ref[len - 1] == '/')
			ref[--len] = '\0';
		if (!hide_refs) {
			hide_refs = xcalloc(1, sizeof(*hide_refs));
			hide_refs->strdup_strings = 1;
		}
		string_list_append(hide_refs, ref);
	}
	return 0;
}