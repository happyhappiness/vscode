static int64_t
file_seek(struct archive *a, void *client_data, int64_t request, int whence)
{
	struct read_file_data *mine = (struct read_file_data *)client_data;
	int64_t r;

	/* We use off_t here because lseek() is declared that way. */
	/* See above for notes about when off_t is less than 64 bits. */
	r = lseek(mine->fd, request, whence);
	if (r >= 0)
		return r;

	/* If the input is corrupted or truncated, fail. */
	if (mine->filename_type == FNT_STDIN)
		archive_set_error(a, errno, "Error seeking in stdin");
	else if (mine->filename_type == FNT_MBS)
		archive_set_error(a, errno, "Error seeking in '%s'",
		    mine->filename.m);
	else
		archive_set_error(a, errno, "Error seeking in '%S'",
		    mine->filename.w);
	return (ARCHIVE_FATAL);
}