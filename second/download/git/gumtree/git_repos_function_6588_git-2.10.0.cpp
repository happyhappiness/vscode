static void *xstrdup(const char *s1)
{
	void *ret = strdup(s1);
	if (!ret)
		die("Out of memory");
	return ret;
}