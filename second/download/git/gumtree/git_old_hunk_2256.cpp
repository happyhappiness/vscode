		pattern = NULL;

	if (verify) {
		if (!pattern)
			die("--verify requires a reference");
		while (*pattern) {
			unsigned char sha1[20];

			if (starts_with(*pattern, "refs/") &&
			    !read_ref(*pattern, sha1)) {
				if (!quiet)
					show_one(*pattern, sha1);
			}
			else if (!quiet)
				die("'%s' - not a valid ref", *pattern);
			else
				return 1;
			pattern++;
