static int ll_union_merge(const struct ll_merge_driver *drv_unused,
			  mmbuffer_t *result,
			  const char *path_unused,
			  mmfile_t *orig, const char *orig_name,
			  mmfile_t *src1, const char *name1,
			  mmfile_t *src2, const char *name2,
			  const struct ll_merge_options *opts,
			  int marker_size)
{
	/* Use union favor */
	struct ll_merge_options o;
	assert(opts);
	o = *opts;
	o.variant = XDL_MERGE_FAVOR_UNION;
	return ll_xdl_merge(drv_unused, result, path_unused,
			    orig, NULL, src1, NULL, src2, NULL,
			    &o, marker_size);
}