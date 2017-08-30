	ssize_t size;

	void *value = NULL;



#if HAVE_FGETXATTR

	if (fd >= 0)

		size = fgetxattr(fd, name, NULL, 0);

	else if (!a->follow_symlinks)

		size = lgetxattr(accpath, name, NULL, 0);

	else

		size = getxattr(accpath, name, NULL, 0);

#elif HAVE_FGETEA

	if (fd >= 0)

		size = fgetea(fd, name, NULL, 0);

	else if (!a->follow_symlinks)

		size = lgetea(accpath, name, NULL, 0);

	else

		size = getea(accpath, name, NULL, 0);

#endif



	if (size == -1) {

		archive_set_error(&a->archive, errno,

