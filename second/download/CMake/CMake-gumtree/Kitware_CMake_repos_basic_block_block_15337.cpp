{
	struct write_memory_data *mine;

	mine = (struct write_memory_data *)calloc(1, sizeof(*mine));
	if (mine == NULL) {
		archive_set_error(a, ENOMEM, "No memory");
		return (ARCHIVE_FATAL);
	}
	mine->buff = buff;
	mine->size = buffSize;
	mine->client_size = used;
	return (archive_write_open(a, mine,
		    memory_write_open, memory_write, memory_write_close));
}