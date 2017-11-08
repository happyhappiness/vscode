int readlink_stat(const char *Path, STRUCT_STAT * Buffer, char *Linkbuf)
{
#if SUPPORT_LINKS
	if (copy_links) {
		return do_stat(Path, Buffer);
	}
	if (do_lstat(Path, Buffer) == -1) {
		return -1;
	}
	if (S_ISLNK(Buffer->st_mode)) {
		int l;
		if ((l =
		     readlink((char *) Path, Linkbuf,
			      MAXPATHLEN - 1)) == -1) {
			return -1;
		}
		Linkbuf[l] = 0;
		if (copy_unsafe_links && (topsrcname[0] != '\0') &&
		    unsafe_symlink(Linkbuf, topsrcname)) {
			return do_stat(Path, Buffer);
		}
	}
	return 0;
#else
	return do_stat(Path, Buffer);
#endif
}