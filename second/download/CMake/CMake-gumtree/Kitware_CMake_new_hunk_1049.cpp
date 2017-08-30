#endif

	/* TODO: Add an "is_tape_like" variable and appropriate tests. */



	/* Disk-like devices prefer power-of-two block sizes.  */

	/* Use provided block_size as a guide so users have some control. */

	if (is_disk_like) {

		size_t new_block_size = 64 * 1024;

		while (new_block_size < mine->block_size

		    && new_block_size < 64 * 1024 * 1024)

			new_block_size *= 2;

		mine->block_size = new_block_size;

	}

	buffer = malloc(mine->block_size);

	if (mine == NULL || buffer == NULL) {

		archive_set_error(a, ENOMEM, "No memory");

		free(mine);

		free(buffer);

		return (ARCHIVE_FATAL);

	}

	mine->buffer = buffer;

	mine->fd = fd;

	/* Remember mode so close can decide whether to flush. */

	mine->st_mode = st.st_mode;



	/* Disk-like inputs can use lseek(). */

	if (is_disk_like)

		mine->use_lseek = 1;



	return (ARCHIVE_OK);

}



static ssize_t

