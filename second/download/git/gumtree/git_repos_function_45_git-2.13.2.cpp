struct userdiff_driver *userdiff_find_by_path(const char *path)
{
	static struct attr_check *check;

	if (!check)
		check = attr_check_initl("diff", NULL);
	if (!path)
		return NULL;
	if (git_check_attr(path, check))
		return NULL;

	if (ATTR_TRUE(check->items[0].value))
		return &driver_true;
	if (ATTR_FALSE(check->items[0].value))
		return &driver_false;
	if (ATTR_UNSET(check->items[0].value))
		return NULL;
	return userdiff_find_by_name(check->items[0].value);
}