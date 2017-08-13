static ssize_t
memory_write(struct archive *a, void *client_data, const void *buff, size_t length)
{
	struct write_memory_data *mine;
	mine = client_data;

	if (mine->used + length > mine->size) {
		archive_set_error(a, ENOMEM, "Buffer exhausted");
		return (ARCHIVE_FATAL);
	}
	memcpy(mine->buff + mine->used, buff, length);
	mine->used += length;
	if (mine->client_size != NULL)
		*mine->client_size = mine->used;
	return (length);
}