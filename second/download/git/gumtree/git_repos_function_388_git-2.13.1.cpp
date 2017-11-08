static int write_shared_index(struct index_state *istate,
			      struct lock_file *lock, unsigned flags)
{
	struct split_index *si = istate->split_index;
	int fd, ret;

	fd = mks_tempfile(&temporary_sharedindex, git_path("sharedindex_XXXXXX"));
	if (fd < 0) {
		hashclr(si->base_sha1);
		return do_write_locked_index(istate, lock, flags);
	}
	move_cache_to_base_index(istate);
	ret = do_write_index(si->base, fd, 1);
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

	return ret;
}