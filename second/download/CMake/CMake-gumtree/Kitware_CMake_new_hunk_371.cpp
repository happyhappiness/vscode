	struct mtree_entry *entry;
	struct mtree_option *iter;
	const char *next, *eq, *name, *end;
	size_t name_len, len;
	int r, i;

	if ((entry = malloc(sizeof(*entry))) == NULL) {
		archive_set_error(&a->archive, errno, "Can't allocate memory");
