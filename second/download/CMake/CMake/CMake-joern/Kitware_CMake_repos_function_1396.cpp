static ssize_t
file_read(struct archive *a, void *client_data, const void **buff)
{
	struct read_file_data *mine = (struct read_file_data *)client_data;
	ssize_t bytes_read;

	/* TODO: If a recent lseek() operation has left us
	 * mis-aligned, read and return a short block to try to get
	 * us back in alignment. */

	/* TODO: Someday, try mmap() here; if that succeeds, give
	 * the entire file to libarchive as a single block.  That
	 * could be a lot faster than block-by-block manual I/O. */

	/* TODO: We might be able to improve performance on pipes and
	 * sockets by setting non-blocking I/O and just accepting
	 * whatever we get here instead of waiting for a full block
	 * worth of data. */

	*buff = mine->buffer;
	for (;;) {
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
}