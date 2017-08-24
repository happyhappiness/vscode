(archive_sha512_init(&mtree->sha512ctx) == ARCHIVE_OK)
			mtree->compute_sum |= F_SHA512;
		else
			mtree->keys &= ~F_SHA512