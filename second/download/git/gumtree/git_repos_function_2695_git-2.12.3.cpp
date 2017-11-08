static inline int xmks_tempfile(struct tempfile *tempfile,
				const char *template)
{
	return xmks_tempfile_m(tempfile, template, 0600);
}