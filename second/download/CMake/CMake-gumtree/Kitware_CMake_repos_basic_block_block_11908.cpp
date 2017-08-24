{
		/*
		 * Make sure a file-type is set.
		 * The mode has been overridden if it is in the extended data.
		 */
		lha->mode = (lha->mode & ~AE_IFMT) |
		    ((lha->directory)? AE_IFDIR: AE_IFREG);
	}