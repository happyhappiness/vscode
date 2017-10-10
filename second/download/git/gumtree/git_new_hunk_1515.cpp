				   peel_error ? NULL : peeled.hash);
	}

	if (ok != ITER_DONE)
		die("error while iterating over references");

	if (commit_lock_file(&refs->packed_refs_lock)) {
		save_errno = errno;
		error = -1;
	}
	release_packed_ref_cache(packed_ref_cache);
	errno = save_errno;
	return error;
}

/*
