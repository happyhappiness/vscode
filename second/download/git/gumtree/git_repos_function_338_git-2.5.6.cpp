static int write_shared_index(struct index_state *istate,
			      struct lock_file *lock, unsigned flags)
{
	struct split_index *si = istate->split_index;
	static int installed_handler;
	int fd, ret;

	temporary_sharedindex = git_pathdup("sharedindex_XXXXXX");
	fd = mkstemp(temporary_sharedindex);
	if (fd < 0) {
		free(temporary_sharedindex);
		temporary_sharedindex = NULL;
		hashclr(si->base_sha1);
		return do_write_locked_index(istate, lock, flags);
	}
	if (!installed_handler) {
		atexit(remove_temporary_sharedindex);
		sigchain_push_common(remove_temporary_sharedindex_on_signal);
	}
	move_cache_to_base_index(istate);
	ret = do_write_index(si->base, fd, 1);
	close(fd);
	if (ret) {
		remove_temporary_sharedindex();
		return ret;
	}
	ret = rename(temporary_sharedindex,
		     git_path("sharedindex.%s", sha1_to_hex(si->base->sha1)));
	free(temporary_sharedindex);
	temporary_sharedindex = NULL;
	if (!ret)
		hashcpy(si->base_sha1, si->base->sha1);
	return ret;
}