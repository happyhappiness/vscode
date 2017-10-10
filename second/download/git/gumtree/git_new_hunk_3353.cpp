	for (sub = subs; *sub; ++sub) {
		free(name);
		name = xstrfmt("%s/%s", path, *sub);
		if ((dir = opendir(name)) == NULL) {
			if (errno == ENOENT)
				continue;
			error_errno("cannot opendir %s", name);
			goto out;
		}

		while ((dent = readdir(dir)) != NULL) {
			if (dent->d_name[0] == '.')
				continue;
