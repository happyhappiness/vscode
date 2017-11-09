static inline int mks_tempfile(struct tempfile *tempfile,
			       const char *template)
{
	return mks_tempfile_sm(tempfile, template, 0, 0600);
}