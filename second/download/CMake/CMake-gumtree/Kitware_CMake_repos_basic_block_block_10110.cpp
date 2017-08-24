{
		bytes_read = read(mine->fd, mine->buffer, mine->block_size);
		if (bytes_read < 0) {
			if (errno == EINTR)
				continue;
			else if (mine->filename_type == FNT_STDIN)
				archive_set_error(a, errno,
				    "Error reading stdin");
			else if (mine->filename_type == FNT_MBS)
				archive_set_error(a, errno,
				    "Error reading '%s'", mine->filename.m);
			else
				archive_set_error(a, errno,
				    "Error reading '%S'", mine->filename.w);
		}
		return (bytes_read);
	}