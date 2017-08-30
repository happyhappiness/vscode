		mine->block_size = new_block_size;

	}

	buffer = malloc(mine->block_size);

	if (buffer == NULL) {

		archive_set_error(a, ENOMEM, "No memory");

		goto fail;

	}

	mine->buffer = buffer;

	mine->fd = fd;

