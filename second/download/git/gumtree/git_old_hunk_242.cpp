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
