{
		mtree->resolver = archive_entry_linkresolver_new();
		if (mtree->resolver == NULL)
			return ARCHIVE_FATAL;
		archive_entry_linkresolver_set_strategy(mtree->resolver,
		    ARCHIVE_FORMAT_MTREE);
		r = read_mtree(a, mtree);
		if (r != ARCHIVE_OK)
			return (r);
	}