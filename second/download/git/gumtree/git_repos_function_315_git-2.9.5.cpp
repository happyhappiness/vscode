int index_name_pos(const struct index_state *istate, const char *name, int namelen)
{
	return index_name_stage_pos(istate, name, namelen, 0);
}