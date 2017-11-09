int git_check_attr(const char *path, struct attr_check *check)
{
	int i;

	collect_some_attrs(path, check);

	for (i = 0; i < check->nr; i++) {
		size_t n = check->items[i].attr->attr_nr;
		const char *value = check->all_attrs[n].value;
		if (value == ATTR__UNKNOWN)
			value = ATTR__UNSET;
		check->items[i].value = value;
	}

	return 0;
}