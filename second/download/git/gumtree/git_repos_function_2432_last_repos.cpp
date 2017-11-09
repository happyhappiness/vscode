static int ll_binary_merge(const struct ll_merge_driver *drv_unused,
			   mmbuffer_t *result,
			   const char *path,
			   mmfile_t *orig, const char *orig_name,
			   mmfile_t *src1, const char *name1,
			   mmfile_t *src2, const char *name2,
			   const struct ll_merge_options *opts,
			   int marker_size)
{
	mmfile_t *stolen;
	assert(opts);

	/*
	 * The tentative merge result is the common ancestor for an
	 * internal merge.  For the final merge, it is "ours" by
	 * default but -Xours/-Xtheirs can tweak the choice.
	 */
	if (opts->virtual_ancestor) {
		stolen = orig;
	} else {
		switch (opts->variant) {
		default:
			warning("Cannot merge binary files: %s (%s vs. %s)",
				path, name1, name2);
			/* fallthru */
		case XDL_MERGE_FAVOR_OURS:
			stolen = src1;
			break;
		case XDL_MERGE_FAVOR_THEIRS:
			stolen = src2;
			break;
		}
	}

	result->ptr = stolen->ptr;
	result->size = stolen->size;
	stolen->ptr = NULL;

	/*
	 * With -Xtheirs or -Xours, we have cleanly merged;
	 * otherwise we got a conflict.
	 */
	return (opts->variant ? 0 : 1);
}