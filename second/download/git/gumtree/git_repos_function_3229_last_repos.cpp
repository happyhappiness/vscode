static void debug_path(struct traverse_info *info)
{
	if (info->prev) {
		debug_path(info->prev);
		if (*info->prev->name.path)
			putchar('/');
	}
	printf("%s", info->name.path);
}