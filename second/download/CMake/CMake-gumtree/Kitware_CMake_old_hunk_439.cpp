	 * We don't have lz4 library, and execute external lz4 program
	 * instead.
	 */
	data->pdata = __archive_write_program_allocate();
	if (data->pdata == NULL) {
		free(data);
		archive_set_error(&a->archive, ENOMEM, "Out of memory");
