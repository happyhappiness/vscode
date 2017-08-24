{
#if defined(_WIN32) && !defined(__CYGWIN__)
		if (data->child)
			CloseHandle(data->child);
#endif
		free(data->program_name);
		free(data->child_buf);
		free(data);
	}