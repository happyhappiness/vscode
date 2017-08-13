{
		close(data->child_stdin);
		data->child_stdin = -1;
		close(data->child_stdout);
		data->child_stdout = -1;
		archive_set_error(f->archive, EINVAL,
		    "Can't initialise filter");
		return (ARCHIVE_FATAL);
	}