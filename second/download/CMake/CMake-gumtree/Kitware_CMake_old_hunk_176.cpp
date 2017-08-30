				 * NULL pointer to strlen().  */
	switch (key[0]) {
	case 'G':
		/* GNU "0.0" sparse pax format. */
		if (strcmp(key, "GNU.sparse.numblocks") == 0) {
			tar->sparse_offset = -1;
