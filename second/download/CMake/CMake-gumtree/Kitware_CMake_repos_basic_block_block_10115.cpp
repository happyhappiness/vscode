{
	struct read_file_data *mine = (struct read_file_data *)client_data;

	/* Delegate skip requests. */
	if (mine->use_lseek)
		return (file_skip_lseek(a, client_data, request));

	/* If we can't skip, return 0; libarchive will read+discard instead. */
	return (0);
}