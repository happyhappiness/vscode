((hay = memchr(hay, *needle, haysize)) == NULL) {
		/* trivial */
		return NULL;
	}