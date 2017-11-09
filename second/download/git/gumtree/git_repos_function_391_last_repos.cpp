static int write_split_index(struct index_state *istate,
			     struct lock_file *lock,
			     unsigned flags)
{
	int ret;
	prepare_to_write_split_index(istate);
	ret = do_write_locked_index(istate, lock, flags);
	finish_writing_split_index(istate);
	return ret;
}