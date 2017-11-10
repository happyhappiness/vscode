static int option_parse_directory(const struct option *opt,
				  const char *arg, int unset)
{
	root_len = strlen(arg);
	if (root_len && arg[root_len - 1] != '/') {
		char *new_root;
		root = new_root = xmalloc(root_len + 2);
		strcpy(new_root, arg);
		strcpy(new_root + root_len++, "/");
	} else
		root = arg;
	return 0;
}