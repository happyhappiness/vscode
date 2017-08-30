#endif

	/* TODO: Add an "is_tape_like" variable and appropriate tests. */



	if (filename_type == FNT_WCS)

		mine = (struct read_file_data *)calloc(1,

		    sizeof(*mine) + wcslen(wfilename) * sizeof(wchar_t));

	else

		mine = (struct read_file_data *)calloc(1,

		    sizeof(*mine) + strlen(filename));

	/* Disk-like devices prefer power-of-two block sizes.  */

	/* Use provided block_size as a guide so users have some control. */

	if (is_disk_like) {

		size_t new_block_size = 64 * 1024;

		while (new_block_size < block_size

		    && new_block_size < 64 * 1024 * 1024)

			new_block_size *= 2;

		block_size = new_block_size;

	}

	buffer = malloc(block_size);

	if (mine == NULL || buffer == NULL) {

		archive_set_error(a, ENOMEM, "No memory");

		free(mine);

		free(buffer);

		return (ARCHIVE_FATAL);

	}

	if (filename_type == FNT_WCS)

		wcscpy(mine->filename.w, wfilename);

	else

		strcpy(mine->filename.m, filename);

	mine->filename_type = filename_type;

	mine->block_size = block_size;

	mine->buffer = buffer;

	mine->fd = fd;

	/* Remember mode so close can decide whether to flush. */

	mine->st_mode = st.st_mode;



	/* Disk-like inputs can use lseek(). */

	if (is_disk_like) {

		archive_read_set_seek_callback(a, file_seek);

		mine->use_lseek = 1;

	}



	archive_read_set_read_callback(a, file_read);

	archive_read_set_skip_callback(a, file_skip);

	archive_read_set_close_callback(a, file_close);

	archive_read_set_callback_data(a, mine);

	return (archive_read_open1(a));

}



static ssize_t

