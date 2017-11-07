static void diagnose_invalid_sha1_path(const char *prefix,
				       const char *filename,
				       const unsigned char *tree_sha1,
				       const char *object_name,
				       int object_name_len)
{
	struct stat st;
	unsigned char sha1[20];
	unsigned mode;

	if (!prefix)
		prefix = "";

	if (!lstat(filename, &st))
		die("Path '%s' exists on disk, but not in '%.*s'.",
		    filename, object_name_len, object_name);
	if (errno == ENOENT || errno == ENOTDIR) {
		char *fullname = xmalloc(strlen(filename)
					     + strlen(prefix) + 1);
		strcpy(fullname, prefix);
		strcat(fullname, filename);

		if (!get_tree_entry(tree_sha1, fullname,
				    sha1, &mode)) {
			die("Path '%s' exists, but not '%s'.\n"
			    "Did you mean '%.*s:%s' aka '%.*s:./%s'?",
			    fullname,
			    filename,
			    object_name_len, object_name,
			    fullname,
			    object_name_len, object_name,
			    filename);
		}
		die("Path '%s' does not exist in '%.*s'",
		    filename, object_name_len, object_name);
	}
}