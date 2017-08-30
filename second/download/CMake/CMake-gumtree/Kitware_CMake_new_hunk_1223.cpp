		*rr_moved = rrmoved;

	}

	/*

	 * Make a clone of curent which is going to be relocated

	 * to rr_moved.

	 */

	mvent = isoent_clone(curent);

	if (mvent == NULL) {

		archive_set_error(&a->archive, ENOMEM,

		    "Can't allocate memory");

		return (ARCHIVE_FATAL);

	}

	/* linking..  and use for creating "CL", "PL" and "RE" */

	mvent->rr_parent = curent->parent;

	curent->rr_child = mvent;

	/*

	 * Move subdirectories from the curent to mvent

	 */

	if (curent->children.first != NULL) {

		*mvent->children.last = curent->children.first;

		mvent->children.last = curent->children.last;

	}

	for (np = mvent->children.first; np != NULL; np = np->chnext)

		np->parent = mvent;

	mvent->children.cnt = curent->children.cnt;

	curent->children.cnt = 0;

	curent->children.first = NULL;

	curent->children.last = &curent->children.first;



	if (curent->subdirs.first != NULL) {

		*mvent->subdirs.last = curent->subdirs.first;

		mvent->subdirs.last = curent->subdirs.last;

	}

	mvent->subdirs.cnt = curent->subdirs.cnt;

	curent->subdirs.cnt = 0;

	curent->subdirs.first = NULL;

	curent->subdirs.last = &curent->subdirs.first;



	/*

	 * The mvent becomes a child of the rr_moved entry.

