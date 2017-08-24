
	/* First item is set up a lot like a symlink traversal. */
	/* printf("Looking for wildcard in %s\n", path); */
	/* TODO: wildcard detection here screws up on \\?\c:\ UNC names */
	if (wcschr(base, L'*') || wcschr(base, L'?')) {
		// It has a wildcard in it...
		// Separate the last element.
		p = wcsrchr(base, L'/');
