static int
setup_current_filesystem(struct archive_read_disk *a)
{
	struct tree *t = a->tree;
#if defined(_PC_NAME_MAX) && defined(HAVE_READDIR_R)
	long nm;
#endif
	t->current_filesystem->synthetic = -1;/* Not supported */
	t->current_filesystem->remote = -1;/* Not supported */
	t->current_filesystem->noatime = 0;
	(void)get_xfer_size(t, -1, ".");/* Dummy call to avoid build error. */
	t->current_filesystem->xfer_align = -1;/* Unknown */
	t->current_filesystem->max_xfer_size = -1;
	t->current_filesystem->min_xfer_size = -1;
	t->current_filesystem->incr_xfer_size = -1;

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
		/*
		 * Some sysmtes (HP-UX or others?) incorrectly defined
		 * NAME_MAX macro to be a smaller value.
		 */
#  if defined(NAME_MAX) && NAME_MAX >= 255
		t->current_filesystem->name_max = NAME_MAX;
#  else
		/* No way to get a trusted value of maximum filename
		 * length. */
		t->current_filesystem->name_max = PATH_MAX;
#  endif /* NAME_MAX */
#  if defined(_PC_NAME_MAX)
	else
		t->current_filesystem->name_max = nm;
#  endif /* _PC_NAME_MAX */
#endif /* HAVE_READDIR_R */
	return (ARCHIVE_OK);
}