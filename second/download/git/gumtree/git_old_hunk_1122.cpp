		return error(_("path '%s': cannot merge"), path);
	}

	/*
	 * NEEDSWORK:
	 * There is absolutely no reason to write this as a blob object
	 * and create a phony cache entry just to leak.  This hack is
	 * primarily to get to the write_entry() machinery that massages
	 * the contents to work-tree format and writes out which only
	 * allows it for a cache entry.  The code in write_entry() needs
	 * to be refactored to allow us to feed a <buffer, size, mode>
	 * instead of a cache entry.  Such a refactoring would help
	 * merge_recursive as well (it also writes the merge result to the
	 * object database even when it may contain conflicts).
	 */
	if (write_sha1_file(result_buf.ptr, result_buf.size,
			    blob_type, oid.hash))
		die(_("Unable to add merge result for '%s'"), path);
	ce = make_cache_entry(mode, oid.hash, path, 2, 0);
	if (!ce)
		die(_("make_cache_entry failed for path '%s'"), path);
	status = checkout_entry(ce, state, NULL);
	return status;
}

static int checkout_paths(const struct checkout_opts *opts,
			  const char *revision)
{
