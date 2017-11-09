static void *three_way_filemerge(const char *path, mmfile_t *base, mmfile_t *our, mmfile_t *their, unsigned long *size)
{
	int merge_status;
	mmbuffer_t res;

	/*
	 * This function is only used by cmd_merge_tree, which
	 * does not respect the merge.conflictstyle option.
	 * There is no need to worry about a label for the
	 * common ancestor.
	 */
	merge_status = ll_merge(&res, path, base, NULL,
				our, ".our", their, ".their", NULL);
	if (merge_status < 0)
		return NULL;

	*size = res.size;
	return res.ptr;
}