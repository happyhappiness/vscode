		return 0;

	len = check_leading_path(ce->name, ce_namelen(ce));
	if (!len)
		return 0;
	else if (len > 0) {
		char path[PATH_MAX + 1];
		memcpy(path, ce->name, len);
		path[len] = 0;
		if (lstat(path, &st))
			return error("cannot stat '%s': %s", path,
					strerror(errno));

		return check_ok_to_remove(path, len, DT_UNKNOWN, NULL, &st,
				error_type, o);
	} else if (lstat(ce->name, &st)) {
		if (errno != ENOENT)
			return error("cannot stat '%s': %s", ce->name,
				     strerror(errno));
		return 0;
	} else {
