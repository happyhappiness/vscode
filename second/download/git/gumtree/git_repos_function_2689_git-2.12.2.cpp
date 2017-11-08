static inline int mks_tempfile_m(struct tempfile *tempfile,
				 const char *template, int mode)
{
	return mks_tempfile_sm(tempfile, template, 0, mode);
}