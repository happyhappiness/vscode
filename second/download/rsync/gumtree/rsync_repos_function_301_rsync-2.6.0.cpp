int link_stat(const char *path, STRUCT_STAT * buffer)
{
#if SUPPORT_LINKS
	if (copy_links) {
		return do_stat(path, buffer);
	} else {
		return do_lstat(path, buffer);
	}
#else
	return do_stat(path, buffer);
#endif
}