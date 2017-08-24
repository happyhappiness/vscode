{
		free(data->path);
		if (data->argv != NULL) {
			int i;
			for (i = 0; data->argv[i] != NULL; i++)
				free(data->argv[i]);
			free(data->argv);
		}
		free(data);
	}