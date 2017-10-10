	move_cache_to_base_index(istate);
	ret = do_write_index(si->base, &temporary_sharedindex, 1);
	if (ret) {
		delete_tempfile(&temporary_sharedindex);
		return ret;
	}
	ret = rename_tempfile(&temporary_sharedindex,
			      git_path("sharedindex.%s", sha1_to_hex(si->base->sha1)));
	if (!ret) {
		hashcpy(si->base_sha1, si->base->sha1);
		clean_shared_index_files(sha1_to_hex(si->base->sha1));
	}
