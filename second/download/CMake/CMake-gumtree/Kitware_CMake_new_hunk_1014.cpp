	t->current_filesystem->synthetic = -1;

	t->current_filesystem->remote = -1;

	if (tree_current_is_symblic_link_target(t)) {

#if defined(HAVE_OPENAT)

		/*

		 * Get file system statistics on any directory

		 * where current is.

		 */

		int fd = openat(tree_current_dir_fd(t),

		    tree_current_access_path(t), O_RDONLY | O_CLOEXEC);

		__archive_ensure_cloexec_flag(fd);

		if (fd < 0) {

			archive_set_error(&a->archive, errno,

			    "openat failed");

