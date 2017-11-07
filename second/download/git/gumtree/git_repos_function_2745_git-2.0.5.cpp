static struct merge_file_info
merge_file_special_markers(struct merge_options *o,
			   const struct diff_filespec *one,
			   const struct diff_filespec *a,
			   const struct diff_filespec *b,
			   const char *branch1,
			   const char *filename1,
			   const char *branch2,
			   const char *filename2)
{
	char *side1 = NULL;
	char *side2 = NULL;
	struct merge_file_info mfi;

	if (filename1) {
		side1 = xmalloc(strlen(branch1) + strlen(filename1) + 2);
		sprintf(side1, "%s:%s", branch1, filename1);
	}
	if (filename2) {
		side2 = xmalloc(strlen(branch2) + strlen(filename2) + 2);
		sprintf(side2, "%s:%s", branch2, filename2);
	}

	mfi = merge_file_1(o, one, a, b,
			   side1 ? side1 : branch1, side2 ? side2 : branch2);
	free(side1);
	free(side2);
	return mfi;
}