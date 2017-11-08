int git_check_attr(const char *path, int num, struct git_attr_check *check)
{
	int i;

	collect_some_attrs(path, num, check);

	for (i = 0; i < num; i++) {
		const char *value = check_all_attr[check[i].attr->attr_nr].value;
		if (value == ATTR__UNKNOWN)
			value = ATTR__UNSET;
		check[i].value = value;
	}

	return 0;
}