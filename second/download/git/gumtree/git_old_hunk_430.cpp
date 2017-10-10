
		/* Subdirectory match - error out */
		return error("%s: is a directory - add individual files instead", path);
	}

	/* No match - should we add it as a gitlink? */
	if (!resolve_gitlink_ref(path, "HEAD", sha1))
		return add_one_path(NULL, path, len, st);

	/* Error out. */
	return error("%s: is a directory - add files inside instead", path);
}

