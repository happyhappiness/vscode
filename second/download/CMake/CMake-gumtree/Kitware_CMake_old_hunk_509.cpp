
	switch(rsrc->compression) {
	case 0:  /* No compression. */
#ifdef HAVE_ZLIB_H
	case 8: /* Deflate compression. */
#endif
