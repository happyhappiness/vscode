{
		free(data->cmd);
		archive_string_free(&data->description);
		__archive_write_program_free(data->pdata);
		free(data);
		f->data = NULL;
	}