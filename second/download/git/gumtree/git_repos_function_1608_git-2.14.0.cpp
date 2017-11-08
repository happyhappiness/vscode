void diff_free_filespec_data(struct diff_filespec *s)
{
	diff_free_filespec_blob(s);
	FREE_AND_NULL(s->cnt_data);
}