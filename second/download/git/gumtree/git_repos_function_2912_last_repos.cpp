static inline int mks_tempfile_ts(struct tempfile *tempfile,
				  const char *template, int suffixlen)
{
	return mks_tempfile_tsm(tempfile, template, suffixlen, 0600);
}