static ssize_t
file_read(struct archive *a, void *client_data, const void **buff)
{
	struct read_FILE_data *mine = (struct read_FILE_data *)client_data;
	size_t bytes_read;

	*buff = mine->buffer;
	bytes_read = fread(mine->buffer, 1, mine->block_size, mine->f);
	if (bytes_read < mine->block_size && ferror(mine->f)) {
		archive_set_error(a, errno, "Error reading file");
	}
	return (bytes_read);
}