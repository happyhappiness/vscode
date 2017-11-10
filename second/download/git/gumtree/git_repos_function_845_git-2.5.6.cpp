int read_index_preload(struct index_state *index,
		       const struct pathspec *pathspec)
{
	int retval = read_index(index);

	preload_index(index, pathspec);
	return retval;
}