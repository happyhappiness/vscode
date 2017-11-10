char *prefix_path_gently(const char *prefix, int len,
			 int *remaining_prefix, const char *path)
{
	const char *orig = path;
	char *sanitized;
	if (is_absolute_path(orig)) {
		sanitized = xmalloc(strlen(path) + 1);
		if (remaining_prefix)
			*remaining_prefix = 0;
		if (normalize_path_copy_len(sanitized, path, remaining_prefix)) {
			free(sanitized);
			return NULL;
		}
		if (abspath_part_inside_repo(sanitized)) {
			free(sanitized);
			return NULL;
		}
	} else {
		sanitized = xmalloc(len + strlen(path) + 1);
		if (len)
			memcpy(sanitized, prefix, len);
		strcpy(sanitized + len, path);
		if (remaining_prefix)
			*remaining_prefix = len;
		if (normalize_path_copy_len(sanitized, sanitized, remaining_prefix)) {
			free(sanitized);
			return NULL;
		}
	}
	return sanitized;
}