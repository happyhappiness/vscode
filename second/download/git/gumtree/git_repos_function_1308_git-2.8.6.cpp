struct diff_filepair *diff_unmerge(struct diff_options *options, const char *path)
{
	struct diff_filepair *pair;
	struct diff_filespec *one, *two;

	if (options->prefix &&
	    strncmp(path, options->prefix, options->prefix_length))
		return NULL;

	one = alloc_filespec(path);
	two = alloc_filespec(path);
	pair = diff_queue(&diff_queued_diff, one, two);
	pair->is_unmerged = 1;
	return pair;
}