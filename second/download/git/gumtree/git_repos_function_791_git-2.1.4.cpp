static int alias_lookup_cb(const char *k, const char *v, void *cb)
{
	const char *name;
	if (skip_prefix(k, "alias.", &name) && !strcmp(name, alias_key)) {
		if (!v)
			return config_error_nonbool(k);
		alias_val = xstrdup(v);
		return 0;
	}
	return 0;
}