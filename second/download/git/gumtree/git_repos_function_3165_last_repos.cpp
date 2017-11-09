int would_convert_to_git_filter_fd(const char *path)
{
	struct conv_attrs ca;

	convert_attrs(&ca, path);
	if (!ca.drv)
		return 0;

	/*
	 * Apply a filter to an fd only if the filter is required to succeed.
	 * We must die if the filter fails, because the original data before
	 * filtering is not available.
	 */
	if (!ca.drv->required)
		return 0;

	return apply_filter(path, NULL, 0, -1, NULL, ca.drv, CAP_CLEAN, NULL);
}