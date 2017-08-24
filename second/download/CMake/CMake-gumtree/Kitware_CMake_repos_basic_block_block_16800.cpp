(archive_sha384_init(&mtree->sha384ctx) == ARCHIVE_OK)
			mtree->compute_sum |= F_SHA384;
		else
			mtree->keys &= ~F_SHA384