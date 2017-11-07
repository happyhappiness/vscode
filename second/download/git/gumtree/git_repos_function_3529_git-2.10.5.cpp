struct dir_iterator *dir_iterator_begin(const char *path)
{
	struct dir_iterator_int *iter = xcalloc(1, sizeof(*iter));
	struct dir_iterator *dir_iterator = &iter->base;

	if (!path || !*path)
		die("BUG: empty path passed to dir_iterator_begin()");

	strbuf_init(&iter->base.path, PATH_MAX);
	strbuf_addstr(&iter->base.path, path);

	ALLOC_GROW(iter->levels, 10, iter->levels_alloc);

	iter->levels_nr = 1;
	iter->levels[0].initialized = 0;

	return dir_iterator;
}