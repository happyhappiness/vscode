	struct archive_read_disk *a = (struct archive_read_disk *)_a;



	if (a->tree != NULL)

		a->tree = tree_reopen(a->tree, pathname, a->restore_time);

	else

		a->tree = tree_open(pathname, a->symlink_mode,

		    a->restore_time);

	if (a->tree == NULL) {

		archive_set_error(&a->archive, ENOMEM,

		    "Can't allocate tar data");

