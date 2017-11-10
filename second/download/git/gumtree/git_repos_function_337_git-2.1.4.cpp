int stat_validity_check(struct stat_validity *sv, const char *path)
{
	struct stat st;

	if (stat(path, &st) < 0)
		return sv->sd == NULL;
	if (!sv->sd)
		return 0;
	return S_ISREG(st.st_mode) && !match_stat_data(sv->sd, &st);
}