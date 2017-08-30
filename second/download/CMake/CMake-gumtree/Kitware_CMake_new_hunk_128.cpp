	struct archive_read_disk *a = (struct archive_read_disk *)_a;



	if (a->tree != NULL)

		a->tree = tree_reopen(a->tree, pathname,

		    a->flags & ARCHIVE_READDISK_RESTORE_ATIME);

	else

		a->tree = tree_open(pathname, a->symlink_mode,

		    a->flags & ARCHIVE_READDISK_RESTORE_ATIME);

	if (a->tree == NULL) {

		archive_set_error(&a->archive, ENOMEM,

		    "Can't allocate directory traversal data");

