static char *traverse_path(const struct traverse_info *info, const struct name_entry *n)
{
	char *path = xmalloc(traverse_path_len(info, n) + 1);
	return make_traverse_path(path, info, n);
}