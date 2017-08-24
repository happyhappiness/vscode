(archive_sha1_init(&mtree->sha1ctx) == ARCHIVE_OK)
			mtree->compute_sum |= F_SHA1;
		else
			mtree->keys &= ~F_SHA1