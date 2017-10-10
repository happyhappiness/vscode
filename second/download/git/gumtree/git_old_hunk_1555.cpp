	}
	return 0;
}

int check_filename(const char *prefix, const char *arg)
{
	const char *name;
	char *to_free = NULL;
	struct stat st;

	if (starts_with(arg, ":/")) {
		if (arg[2] == '\0') /* ":/" is root dir, always exists */
			return 1;
		name = arg + 2;
	} else if (prefix)
		name = to_free = prefix_filename(prefix, arg);
	else
		name = arg;
	if (!lstat(name, &st)) {
		free(to_free);
		return 1; /* file exists */
	}
	if (errno == ENOENT || errno == ENOTDIR) {
		free(to_free);
		return 0; /* file does not exist */
	}
	die_errno("failed to stat '%s'", arg);
}

