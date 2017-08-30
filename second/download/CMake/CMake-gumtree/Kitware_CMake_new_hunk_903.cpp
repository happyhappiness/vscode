#if defined(HAVE_READDIR_R)

	/* Set maximum filename length. */

#  if defined(_PC_NAME_MAX)

	if (tree_current_is_symblic_link_target(t)) {

		if (tree_enter_working_dir(t) != 0) {

			archive_set_error(&a->archive, errno, "fchdir failed");

			return (ARCHIVE_FAILED);

		}

		nm = pathconf(tree_current_access_path(t), _PC_NAME_MAX);

	} else

		nm = fpathconf(tree_current_dir_fd(t), _PC_NAME_MAX);

	if (nm == -1)

#  endif /* _PC_NAME_MAX */

