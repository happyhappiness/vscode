static const struct attr_check *get_archive_attrs(const char *path)
{
	static struct attr_check *check;
	if (!check)
		check = attr_check_initl("export-ignore", "export-subst", NULL);
	return git_check_attr(path, check) ? NULL : check;
}