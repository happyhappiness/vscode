				   peel_error ? NULL : peeled.hash);
	}

	if (ok != ITER_DONE)
		die("error while iterating over references");

	if (commit_lock_file(packed_ref_cache->lock)) {
		save_errno = errno;
		error = -1;
	}
	packed_ref_cache->lock = NULL;
	release_packed_ref_cache(packed_ref_cache);
	errno = save_errno;
	return error;
}

/*
