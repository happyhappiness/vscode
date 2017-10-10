	if (verify) {
		if (!pattern)
			die("--verify requires a reference");
		while (*pattern) {
			struct object_id oid;

			if ((starts_with(*pattern, "refs/") || !strcmp(*pattern, "HEAD")) &&
			    !read_ref(*pattern, oid.hash)) {
				show_one(*pattern, &oid);
			}
			else if (!quiet)
				die("'%s' - not a valid ref", *pattern);
			else
				return 1;
			pattern++;
