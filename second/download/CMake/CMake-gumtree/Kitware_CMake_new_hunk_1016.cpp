	t->current_filesystem->name_max = sfs.f_namemax;
#else
	/* Mac OS X does not have f_namemax in struct statfs. */
	if (tree_current_is_symblic_link_target(t)) {
		if (tree_enter_working_dir(t) != 0) {
			archive_set_error(&a->archive, errno, "fchdir failed");
			return (ARCHIVE_FAILED);
		}
		nm = pathconf(tree_current_access_path(t), _PC_NAME_MAX);
	} else
		nm = fpathconf(tree_current_dir_fd(t), _PC_NAME_MAX);
	if (nm == -1)
		t->current_filesystem->name_max = NAME_MAX;
