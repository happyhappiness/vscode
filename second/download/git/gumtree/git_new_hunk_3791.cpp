			return retval;
	}
	return 0;
}

/*
 * Load all of the refs from the dir into our in-memory cache. The hard work
 * of loading loose refs is done by get_ref_dir(), so we just need to recurse
 * through all of the sub-directories. We do not even need to care about
 * sorting, as traversal order does not matter to us.
 */
static void prime_ref_dir(struct ref_dir *dir)
