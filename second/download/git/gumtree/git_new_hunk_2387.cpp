static void diagnose_invalid_sha1_path(const char *prefix,
				       const char *filename,
				       const unsigned char *tree_sha1,
				       const char *object_name,
				       int object_name_len)
{
	unsigned char sha1[20];
	unsigned mode;

	if (!prefix)
		prefix = "";

	if (file_exists(filename))
		die("Path '%s' exists on disk, but not in '%.*s'.",
		    filename, object_name_len, object_name);
	if (errno == ENOENT || errno == ENOTDIR) {
		char *fullname = xstrfmt("%s%s", prefix, filename);

		if (!get_tree_entry(tree_sha1, fullname,
