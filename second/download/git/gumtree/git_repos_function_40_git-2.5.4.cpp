struct userdiff_driver *userdiff_find_by_path(const char *path)
{
	static struct git_attr *attr;
	struct git_attr_check check;

	if (!attr)
		attr = git_attr("diff");
	check.attr = attr;

	if (!path)
		return NULL;
	if (git_check_attr(path, 1, &check))
		return NULL;

	if (ATTR_TRUE(check.value))
		return &driver_true;
	if (ATTR_FALSE(check.value))
		return &driver_false;
	if (ATTR_UNSET(check.value))
		return NULL;
	return userdiff_find_by_name(check.value);
}