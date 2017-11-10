static const char *pair_pathtwo(void *obj)
{
	struct diff_filepair *pair = (struct diff_filepair *)obj;

	return pair->two->path;
}