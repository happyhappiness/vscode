    struct archive_entry *, int *fd);

#endif



#if !ARCHIVE_ACL_SUPPORT

int

archive_read_disk_entry_setup_acls(struct archive_read_disk *a,

    struct archive_entry *entry, int *fd)

{

	(void)a;      /* UNUSED */

	(void)entry;  /* UNUSED */

	(void)fd;     /* UNUSED */

	return (ARCHIVE_OK);

}

#endif



/*

 * Enter working directory and return working pathname of archive_entry.

 * If a pointer to an integer is provided and its value is below zero

 * open a file descriptor on this pahtname.

 */

const char *

archive_read_disk_entry_setup_path(struct archive_read_disk *a,

    struct archive_entry *entry, int *fd)

{

	const char *path;



	path = archive_entry_sourcepath(entry);



	if (path == NULL || (a->tree != NULL &&

	    a->tree_enter_working_dir(a->tree) != 0))

		path = archive_entry_pathname(entry);

	if (path == NULL) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		   "Couldn't determine path");

	} else if (fd != NULL && *fd < 0 && a->tree != NULL &&

	    (a->follow_symlinks || archive_entry_filetype(entry) != AE_IFLNK)) {

		*fd = a->open_on_current_dir(a->tree, path,

		    O_RDONLY | O_NONBLOCK);

	}

	return (path);

}



int

archive_read_disk_entry_from_file(struct archive *_a,

    struct archive_entry *entry,

