static int verify_index(const struct index_state *istate)
{
	return verify_index_from(istate, get_index_file());
}