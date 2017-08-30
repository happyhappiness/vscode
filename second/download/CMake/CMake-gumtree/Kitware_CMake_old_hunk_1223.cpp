		*rr_moved = rrmoved;
	}
	/*
	 * Make a clone of isoent which is going to be relocated
	 * to rr_moved.
	 */
	mvent = isoent_clone(isoent);
	if (mvent == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "Can't allocate memory");
		return (ARCHIVE_FATAL);
	}
	/* linking..  and use for creating "CL", "PL" and "RE" */
	mvent->rr_parent = isoent->parent;
	isoent->rr_child = mvent;
	/*
	 * Move subdirectories from the isoent to mvent
	 */
	if (isoent->children.first != NULL) {
		*mvent->children.last = isoent->children.first;
		mvent->children.last = isoent->children.last;
	}
	for (np = mvent->children.first; np != NULL; np = np->chnext)
		np->parent = mvent;
	mvent->children.cnt = isoent->children.cnt;
	isoent->children.cnt = 0;
	isoent->children.first = NULL;
	isoent->children.last = &isoent->children.first;

	if (isoent->subdirs.first != NULL) {
		*mvent->subdirs.last = isoent->subdirs.first;
		mvent->subdirs.last = isoent->subdirs.last;
	}
	mvent->subdirs.cnt = isoent->subdirs.cnt;
	isoent->subdirs.cnt = 0;
	isoent->subdirs.first = NULL;
	isoent->subdirs.last = &isoent->subdirs.first;

	/*
	 * The mvent becomes a child of the rr_moved entry.
