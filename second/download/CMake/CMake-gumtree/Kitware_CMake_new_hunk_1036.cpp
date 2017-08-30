
	/* First item is set up a lot like a symlink traversal. */
	/* printf("Looking for wildcard in %s\n", path); */
	if ((base[0] == L'/' && base[1] == L'/' &&
	     base[2] == L'?' && base[3] == L'/' &&
	     (wcschr(base+4, L'*') || wcschr(base+4, L'?'))) ||
	    (!(base[0] == L'/' && base[1] == L'/' &&
	       base[2] == L'?' && base[3] == L'/') &&
	       (wcschr(base, L'*') || wcschr(base, L'?')))) {
		// It has a wildcard in it...
		// Separate the last element.
		p = wcsrchr(base, L'/');
