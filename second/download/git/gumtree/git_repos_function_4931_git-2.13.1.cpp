static const char **internal_prefix_pathspec(const char *prefix,
					     const char **pathspec,
					     int count, unsigned flags)
{
	int i;
	const char **result;
	int prefixlen = prefix ? strlen(prefix) : 0;
	ALLOC_ARRAY(result, count + 1);

	/* Create an intermediate copy of the pathspec based on the flags */
	for (i = 0; i < count; i++) {
		int length = strlen(pathspec[i]);
		int to_copy = length;
		char *it;
		while (!(flags & KEEP_TRAILING_SLASH) &&
		       to_copy > 0 && is_dir_sep(pathspec[i][to_copy - 1]))
			to_copy--;

		it = xmemdupz(pathspec[i], to_copy);
		if (flags & DUP_BASENAME) {
			result[i] = xstrdup(basename(it));
			free(it);
		} else {
			result[i] = it;
		}
	}
	result[count] = NULL;

	/* Prefix the pathspec and free the old intermediate strings */
	for (i = 0; i < count; i++) {
		const char *match = prefix_path(prefix, prefixlen, result[i]);
		free((char *) result[i]);
		result[i] = match;
	}

	return result;
}