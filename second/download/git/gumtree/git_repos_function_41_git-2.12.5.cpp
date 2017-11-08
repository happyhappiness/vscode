int userdiff_config(const char *k, const char *v)
{
	struct userdiff_driver *drv;
	const char *name, *type;
	int namelen;

	if (parse_config_key(k, "diff", &name, &namelen, &type) || !name)
		return 0;

	drv = userdiff_find_by_namelen(name, namelen);
	if (!drv) {
		ALLOC_GROW(drivers, ndrivers+1, drivers_alloc);
		drv = &drivers[ndrivers++];
		memset(drv, 0, sizeof(*drv));
		drv->name = xmemdupz(name, namelen);
		drv->binary = -1;
	}

	if (!strcmp(type, "funcname"))
		return parse_funcname(&drv->funcname, k, v, 0);
	if (!strcmp(type, "xfuncname"))
		return parse_funcname(&drv->funcname, k, v, REG_EXTENDED);
	if (!strcmp(type, "binary"))
		return parse_tristate(&drv->binary, k, v);
	if (!strcmp(type, "command"))
		return git_config_string(&drv->external, k, v);
	if (!strcmp(type, "textconv"))
		return git_config_string(&drv->textconv, k, v);
	if (!strcmp(type, "cachetextconv"))
		return parse_bool(&drv->textconv_want_cache, k, v);
	if (!strcmp(type, "wordregex"))
		return git_config_string(&drv->word_regex, k, v);

	return 0;
}