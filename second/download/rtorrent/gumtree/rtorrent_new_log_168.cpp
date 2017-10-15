print_buffer(first, last, "Checking hash [%2i%%]",
		       (d->download()->chunks_hashed() * 100) / d->download()->chunks_total());