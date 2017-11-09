void git_all_attrs(const char *path, struct attr_check *check)
{
	int i;

	attr_check_reset(check);
	collect_some_attrs(path, check);

	for (i = 0; i < check->all_attrs_nr; i++) {
		const char *name = check->all_attrs[i].attr->name;
		const char *value = check->all_attrs[i].value;
		struct attr_check_item *item;
		if (value == ATTR__UNSET || value == ATTR__UNKNOWN)
			continue;
		item = attr_check_append(check, git_attr(name));
		item->value = value;
	}
}