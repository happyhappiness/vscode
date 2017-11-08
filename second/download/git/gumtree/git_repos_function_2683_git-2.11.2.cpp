static inline int mks_tempfile_t(struct tempfile *tempfile,
				 const char *template)
{
	return mks_tempfile_tsm(tempfile, template, 0, 0600);
}