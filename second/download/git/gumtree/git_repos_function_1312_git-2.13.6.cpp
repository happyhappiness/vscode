static int read_apply_cache(struct apply_state *state)
{
	if (state->index_file)
		return read_cache_from(state->index_file);
	else
		return read_cache();
}