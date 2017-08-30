		return (ARCHIVE_FATAL);

	}



#if HAVE_FGETXATTR

	if (fd >= 0)

		size = fgetxattr(fd, name, value, size);

	else if (!a->follow_symlinks)

		size = lgetxattr(accpath, name, value, size);

	else

		size = getxattr(accpath, name, value, size);

#elif HAVE_FGETEA

	if (fd >= 0)

		size = fgetea(fd, name, value, size);

	else if (!a->follow_symlinks)

		size = lgetea(accpath, name, value, size);

	else

		size = getea(accpath, name, value, size);

#endif



	if (size == -1) {

		archive_set_error(&a->archive, errno,

