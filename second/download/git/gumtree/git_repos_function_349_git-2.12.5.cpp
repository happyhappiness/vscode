int read_index(struct index_state *istate)
{
	return read_index_from(istate, get_index_file());
}