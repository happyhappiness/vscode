static int get_dtype(struct dirent *de, struct index_state *istate,
		     const char *path, int len)
{
	int dtype = de ? DTYPE(de) : DT_UNKNOWN;
	struct stat st;

	if (dtype != DT_UNKNOWN)
		return dtype;
	dtype = get_index_dtype(istate, path, len);
	if (dtype != DT_UNKNOWN)
		return dtype;
	if (lstat(path, &st))
		return dtype;
	if (S_ISREG(st.st_mode))
		return DT_REG;
	if (S_ISDIR(st.st_mode))
		return DT_DIR;
	if (S_ISLNK(st.st_mode))
		return DT_LNK;
	return dtype;
}