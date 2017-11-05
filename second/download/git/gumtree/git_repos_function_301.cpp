int match_stat_data_racy(const struct index_state *istate,
			 const struct stat_data *sd, struct stat *st)
{
	if (is_racy_stat(istate, sd))
		return MTIME_CHANGED;
	return match_stat_data(sd, st);
}