{
	struct archive_write_program_data *data;

	data = calloc(1, sizeof(struct archive_write_program_data));
	if (data == NULL)
		return (data);
	data->child_stdin = -1;
	data->child_stdout = -1;
	data->program_name = strdup(program);
	return (data);
}