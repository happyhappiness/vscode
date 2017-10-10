	for (sub = subs; *sub; ++sub) {
		free(name);
		name = xstrfmt("%s/%s", path, *sub);
		if ((dir = opendir(name)) == NULL) {
			if (errno == ENOENT)
				continue;
			error("cannot opendir %s (%s)", name, strerror(errno));
			goto out;
		}

		while ((dent = readdir(dir)) != NULL) {
			if (dent->d_name[0] == '.')
				continue;
