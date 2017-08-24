{
#if HAVE_STRUCT_STAT_ST_BLKSIZE
		int r;
		if ((r = lazy_stat(a)) != ARCHIVE_OK)
			return (r);
		block_size = a->pst->st_blksize;
#else
		/* XXX TODO XXX Is there a more appropriate choice here ? */
		/* This needn't match the filesystem allocation size. */
		block_size = 16*1024;
#endif
	}