#if defined(HAVE_READDIR_R)

	/* Set maximum filename length. */

#  if defined(_PC_NAME_MAX)

	if (tree_current_is_symblic_link_target(t))

		nm = pathconf(tree_current_access_path(t), _PC_NAME_MAX);

	else

		nm = fpathconf(tree_current_dir_fd(t), _PC_NAME_MAX);

	if (nm == -1)

#  endif /* _PC_NAME_MAX */

