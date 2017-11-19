struct attr_check *attr_check_initl(const char *one, ...)
{
	struct attr_check *check;
	int cnt;
	va_list params;
	const char *param;

	va_start(params, one);
	for (cnt = 1; (param = va_arg(params, const char *)) != NULL; cnt++)
		;
	va_end(params);

	check = attr_check_alloc();
	check->nr = cnt;
	check->alloc = cnt;
	check->items = xcalloc(cnt, sizeof(struct attr_check_item));

	check->items[0].attr = git_attr(one);
	va_start(params, one);
	for (cnt = 1; cnt < check->nr; cnt++) {
		const struct git_attr *attr;
		param = va_arg(params, const char *);
		if (!param)
			die("BUG: counted %d != ended at %d",
			    check->nr, cnt);
		attr = git_attr(param);
		if (!attr)
			die("BUG: %s: not a valid attribute name", param);
		check->items[cnt].attr = attr;
	}
	va_end(params);
	return check;
}