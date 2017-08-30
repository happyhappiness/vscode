		return (ARCHIVE_FATAL);

	}



#if HAVE_FLISTXATTR

	if (*fd >= 0)

		list_size = flistxattr(*fd, list, list_size);

	else if (!a->follow_symlinks)

		list_size = llistxattr(path, list, list_size);

	else

		list_size = listxattr(path, list, list_size);

#elif HAVE_FLISTEA

	if (*fd >= 0)

		list_size = flistea(*fd, list, list_size);

	else if (!a->follow_symlinks)

		list_size = llistea(path, list, list_size);

	else

		list_size = listea(path, list, list_size);

#endif



	if (list_size == -1) {

		archive_set_error(&a->archive, errno,

