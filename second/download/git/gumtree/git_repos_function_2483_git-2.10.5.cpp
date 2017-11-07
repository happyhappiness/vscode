static inline int mks_tempfile_tm(struct tempfile *tempfile,
				  const char *template, int mode)
{
	return mks_tempfile_tsm(tempfile, template, 0, mode);
}