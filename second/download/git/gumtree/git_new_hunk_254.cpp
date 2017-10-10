			return error("%s", message);
		return -1;
	}
	return -1;
}

/*
 * The tree traversal is looking at name p.  If we have a matching entry,
 * return it.  If name p is a directory in the index, do not return
 * anything, as we will want to match it when the traversal descends into
 * the directory.
 */
