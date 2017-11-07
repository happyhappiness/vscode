static const char **internal_copy_pathspec(const char *prefix,
					   const char **pathspec,
					   int count, unsigned flags)
{
	int i;
	const char **result;
	ALLOC_ARRAY(result, count + 1);
	COPY_ARRAY(result, pathspec, count);
	result[count] = NULL;
	for (i = 0; i < count; i++) {
		int length = strlen(result[i]);
		int to_copy = length;
		while (!(flags & KEEP_TRAILING_SLASH) &&
		       to_copy > 0 && is_dir_sep(result[i][to_copy - 1]))
			to_copy--;
		if (to_copy != length || flags & DUP_BASENAME) {
			char *it = xmemdupz(result[i], to_copy);
			if (flags & DUP_BASENAME) {
				result[i] = xstrdup(basename(it));
				free(it);
			} else
				result[i] = it;
		}
	}
	return get_pathspec(prefix, result);
}