	if (!prefix)
		prefix = "";

	if (file_exists(filename))
		die("Path '%s' exists on disk, but not in '%.*s'.",
		    filename, object_name_len, object_name);
	if (is_missing_file_error(errno)) {
		char *fullname = xstrfmt("%s%s", prefix, filename);

		if (!get_tree_entry(tree_sha1, fullname,
				    sha1, &mode)) {
			die("Path '%s' exists, but not '%s'.\n"
			    "Did you mean '%.*s:%s' aka '%.*s:./%s'?",
