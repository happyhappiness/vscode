{
		bytes_read = read(mine->fd, mine->buffer, mine->block_size);
		if (bytes_read < 0) {
			if (errno == EINTR)
				continue;
			archive_set_error(a, errno, "Error reading fd %d",
			    mine->fd);
		}
		return (bytes_read);
	}