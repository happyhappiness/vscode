	if (path == NULL)

		path = archive_entry_pathname(entry);



	if (*fd < 0 && a->tree != NULL) {

		if (a->follow_symlinks ||

		    archive_entry_filetype(entry) != AE_IFLNK)

			*fd = a->open_on_current_dir(a->tree, path,

				O_RDONLY | O_NONBLOCK);

		if (*fd < 0) {

			if (a->tree_enter_working_dir(a->tree) != 0) {

				archive_set_error(&a->archive, errno,

				    "Couldn't access %s", path);

				return (ARCHIVE_FAILED);

			}

		}

	}



	if (*fd >= 0)

		list_size = extattr_list_fd(*fd, namespace, NULL, 0);

	else if (!a->follow_symlinks)

		list_size = extattr_list_link(path, namespace, NULL, 0);

	else

