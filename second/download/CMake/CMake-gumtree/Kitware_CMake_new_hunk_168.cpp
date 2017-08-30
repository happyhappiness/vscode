	archive_check_magic(_a, ARCHIVE_READ_MAGIC,

	    ARCHIVE_STATE_NEW, "archive_read_support_format_mtree");



	mtree = (struct mtree *)calloc(1, sizeof(*mtree));

	if (mtree == NULL) {

		archive_set_error(&a->archive, ENOMEM,

		    "Can't allocate mtree data");

		return (ARCHIVE_FATAL);

	}

	mtree->fd = -1;



	r = __archive_read_register_format(a, mtree, "mtree",

