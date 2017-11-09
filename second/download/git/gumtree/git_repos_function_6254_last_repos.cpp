static int no_try_delta(const char *path)
{
	static struct attr_check *check;

	if (!check)
		check = attr_check_initl("delta", NULL);
	if (git_check_attr(path, check))
		return 0;
	if (ATTR_FALSE(check->items[0].value))
		return 1;
	return 0;
}