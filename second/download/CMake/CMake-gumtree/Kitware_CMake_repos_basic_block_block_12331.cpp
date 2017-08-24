{
		mtree->buffsize = 64 * 1024;
		mtree->buff = malloc(mtree->buffsize);
		if (mtree->buff == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "Can't allocate memory");
			return (ARCHIVE_FATAL);
		}
	}