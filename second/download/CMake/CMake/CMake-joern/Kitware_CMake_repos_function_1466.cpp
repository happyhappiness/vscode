static int
update_current_filesystem(struct archive_read_disk *a, int64_t dev)
{
	struct tree *t = a->tree;
	int i, fid;

	if (t->current_filesystem != NULL &&
	    t->current_filesystem->dev == dev)
		return (ARCHIVE_OK);

	for (i = 0; i < t->max_filesystem_id; i++) {
		if (t->filesystem_table[i].dev == dev) {
			/* There is the filesystem ID we've already generated. */
			t->current_filesystem_id = i;
			t->current_filesystem = &(t->filesystem_table[i]);
			return (ARCHIVE_OK);
		}
	}

	/*
	 * There is a new filesystem, we generate a new ID for.
	 */
	fid = t->max_filesystem_id++;
	if (t->max_filesystem_id > t->allocated_filesystem) {
		size_t s;
		void *p;

		s = t->max_filesystem_id * 2;
		p = realloc(t->filesystem_table,
			s * sizeof(*t->filesystem_table));
		if (p == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate tar data");
			return (ARCHIVE_FATAL);
		}
		t->filesystem_table = (struct filesystem *)p;
		t->allocated_filesystem = (int)s;
	}
	t->current_filesystem_id = fid;
	t->current_filesystem = &(t->filesystem_table[fid]);
	t->current_filesystem->dev = dev;

	return (setup_current_filesystem(a));
}