		return 0;

	len = check_leading_path(ce->name, ce_namelen(ce));
	if (!len)
		return 0;
	else if (len > 0) {
		char *path;
		int ret;

		path = xmemdupz(ce->name, len);
		if (lstat(path, &st))
			ret = error("cannot stat '%s': %s", path,
					strerror(errno));
		else
			ret = check_ok_to_remove(path, len, DT_UNKNOWN, NULL,
						 &st, error_type, o);
		free(path);
		return ret;
	} else if (lstat(ce->name, &st)) {
		if (errno != ENOENT)
			return error("cannot stat '%s': %s", ce->name,
				     strerror(errno));
		return 0;
	} else {
