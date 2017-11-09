static int try_merge(const struct rerere_id *id, const char *path,
		     mmfile_t *cur, mmbuffer_t *result)
{
	int ret;
	mmfile_t base = {NULL, 0}, other = {NULL, 0};

	if (read_mmfile(&base, rerere_path(id, "preimage")) ||
	    read_mmfile(&other, rerere_path(id, "postimage")))
		ret = 1;
	else
		/*
		 * A three-way merge. Note that this honors user-customizable
		 * low-level merge driver settings.
		 */
		ret = ll_merge(result, path, &base, NULL, cur, "", &other, "", NULL);

	free(base.ptr);
	free(other.ptr);

	return ret;
}