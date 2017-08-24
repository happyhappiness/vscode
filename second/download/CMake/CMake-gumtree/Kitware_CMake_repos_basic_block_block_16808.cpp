(archive_md5_init(&mtree->md5ctx) == ARCHIVE_OK)
			mtree->compute_sum |= F_MD5;
		else
			mtree->keys &= ~F_MD5