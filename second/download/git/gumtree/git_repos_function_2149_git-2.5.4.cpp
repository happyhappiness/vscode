char *xstrdup(const char *str)
{
	char *ret = strdup(str);
	if (!ret) {
		try_to_free_routine(strlen(str) + 1);
		ret = strdup(str);
		if (!ret)
			die("Out of memory, strdup failed");
	}
	return ret;
}