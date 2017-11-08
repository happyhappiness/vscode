int link_stat(const char *path, STRUCT_STAT *buffer, int follow_dirlinks)
{
#ifdef SUPPORT_LINKS
	if (copy_links)
		return do_stat(path, buffer);
	if (do_lstat(path, buffer) < 0)
		return -1;
	if (follow_dirlinks && S_ISLNK(buffer->st_mode)) {
		STRUCT_STAT st;
		if (do_stat(path, &st) == 0 && S_ISDIR(st.st_mode))
			*buffer = st;
	}
	return 0;
#else
	return do_stat(path, buffer);
#endif
}