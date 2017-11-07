static void chmod_path(int flip, const char *path)
{
	int pos;
	struct cache_entry *ce;
	unsigned int mode;

	pos = cache_name_pos(path, strlen(path));
	if (pos < 0)
		goto fail;
	ce = active_cache[pos];
	mode = ce->ce_mode;
	if (!S_ISREG(mode))
		goto fail;
	switch (flip) {
	case '+':
		ce->ce_mode |= 0111; break;
	case '-':
		ce->ce_mode &= ~0111; break;
	default:
		goto fail;
	}
	cache_tree_invalidate_path(active_cache_tree, path);
	active_cache_changed = 1;
	report("chmod %cx '%s'", flip, path);
	return;
 fail:
	die("git update-index: cannot chmod %cx '%s'", flip, path);
}