static int merge_file_special_markers(struct merge_options *o,
			   const struct diff_filespec *one,
			   const struct diff_filespec *a,
			   const struct diff_filespec *b,
			   const char *branch1,
			   const char *filename1,
			   const char *branch2,
			   const char *filename2,
			   struct merge_file_info *mfi)
{
	char *side1 = NULL;
	char *side2 = NULL;
	int ret;

	if (filename1)
		side1 = xstrfmt("%s:%s", branch1, filename1);
	if (filename2)
		side2 = xstrfmt("%s:%s", branch2, filename2);

	ret = merge_file_1(o, one, a, b,
			   side1 ? side1 : branch1,
			   side2 ? side2 : branch2, mfi);
	free(side1);
	free(side2);
	return ret;
}