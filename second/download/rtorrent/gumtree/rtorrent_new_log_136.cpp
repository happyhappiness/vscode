print_buffer(first, last, "Checking hash [%2i%%]",
		       (d->get_download().chunks_hashed() * 100) / d->get_download().chunks_total());