int git_all_attrs(const char *path, int *num, struct git_attr_check **check)
{
	int i, count, j;

	collect_all_attrs(path);

	/* Count the number of attributes that are set. */
	count = 0;
	for (i = 0; i < attr_nr; i++) {
		const char *value = check_all_attr[i].value;
		if (value != ATTR__UNSET && value != ATTR__UNKNOWN)
			++count;
	}
	*num = count;
	*check = xmalloc(sizeof(**check) * count);
	j = 0;
	for (i = 0; i < attr_nr; i++) {
		const char *value = check_all_attr[i].value;
		if (value != ATTR__UNSET && value != ATTR__UNKNOWN) {
			(*check)[j].attr = check_all_attr[i].attr;
			(*check)[j].value = value;
			++j;
		}
	}

	return 0;
}