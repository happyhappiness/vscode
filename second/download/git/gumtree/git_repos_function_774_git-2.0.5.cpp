static int alias_lookup_cb(const char *k, const char *v, void *cb)
{
	if (starts_with(k, "alias.") && !strcmp(k + 6, alias_key)) {
		if (!v)
			return config_error_nonbool(k);
		alias_val = xstrdup(v);
		return 0;
	}
	return 0;
}