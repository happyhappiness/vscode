	path = NULL;



	if (*fd < 0) {

		path = archive_entry_sourcepath(entry);

		if (path == NULL || (a->tree != NULL &&

		    a->tree_enter_working_dir(a->tree) != 0))

			path = archive_entry_pathname(entry);

		if (path == NULL) {

			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

			    "Couldn't determine file path to read "

			    "extended attributes");

			return (ARCHIVE_WARN);

		}

		if (a->tree != NULL && (a->follow_symlinks ||

		    archive_entry_filetype(entry) != AE_IFLNK)) {

			*fd = a->open_on_current_dir(a->tree,

			    path, O_RDONLY | O_NONBLOCK);

		}

	}



#if HAVE_FLISTXATTR

	if (*fd >= 0)

		list_size = flistxattr(*fd, NULL, 0);

	else if (!a->follow_symlinks)

		list_size = llistxattr(path, NULL, 0);

	else

		list_size = listxattr(path, NULL, 0);

#elif HAVE_FLISTEA

	if (*fd >= 0)

		list_size = flistea(*fd, NULL, 0);

	else if (!a->follow_symlinks)

		list_size = llistea(path, NULL, 0);

	else

		list_size = listea(path, NULL, 0);

#endif



	if (list_size == -1) {

		if (errno == ENOTSUP || errno == ENOSYS)

