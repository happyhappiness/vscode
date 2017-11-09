int link_stat(const char *path, STRUCT_STAT *stp, int follow_dirlinks)
{
#ifdef SUPPORT_LINKS
	if (copy_links)
		return x_stat(path, stp, NULL);
	if (x_lstat(path, stp, NULL) < 0)
		return -1;
	if (follow_dirlinks && S_ISLNK(stp->st_mode)) {
		STRUCT_STAT st;
		if (x_stat(path, &st, NULL) == 0 && S_ISDIR(st.st_mode))
			*stp = st;
	}
	return 0;
#else
	return x_stat(path, stp, NULL);
#endif
}