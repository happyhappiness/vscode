(archive_sha256_init(&mtree->sha256ctx) == ARCHIVE_OK)
			mtree->compute_sum |= F_SHA256;
		else
			mtree->keys &= ~F_SHA256