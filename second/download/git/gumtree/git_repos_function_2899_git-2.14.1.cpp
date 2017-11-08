static inline int mks_tempfile_s(struct tempfile *tempfile,
				 const char *template, int suffixlen)
{
	return mks_tempfile_sm(tempfile, template, suffixlen, 0600);
}