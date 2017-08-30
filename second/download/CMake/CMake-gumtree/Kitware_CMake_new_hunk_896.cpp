	int r, xr = 0;



	t->current_filesystem->synthetic = -1;

	if (tree_enter_working_dir(t) != 0) {

		archive_set_error(&a->archive, errno, "fchdir failed");

		return (ARCHIVE_FAILED);

	}

	if (tree_current_is_symblic_link_target(t)) {

		r = statvfs(tree_current_access_path(t), &sfs);

		if (r == 0)

