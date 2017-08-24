(archive_rmd160_init(&mtree->rmd160ctx) == ARCHIVE_OK)
			mtree->compute_sum |= F_RMD160;
		else
			mtree->keys &= ~F_RMD160