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
