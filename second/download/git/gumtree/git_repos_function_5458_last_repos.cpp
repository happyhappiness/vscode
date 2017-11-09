static int fix_unmerged_status(struct diff_filepair *p,
			       struct update_callback_data *data)
{
	if (p->status != DIFF_STATUS_UNMERGED)
		return p->status;
	if (!(data->flags & ADD_CACHE_IGNORE_REMOVAL) && !p->two->mode)
		/*
		 * This is not an explicit add request, and the
		 * path is missing from the working tree (deleted)
		 */
		return DIFF_STATUS_DELETED;
	else
		/*
		 * Either an explicit add request, or path exists
		 * in the working tree.  An attempt to explicitly
		 * add a path that does not exist in the working tree
		 * will be caught as an error by the caller immediately.
		 */
		return DIFF_STATUS_MODIFIED;
}