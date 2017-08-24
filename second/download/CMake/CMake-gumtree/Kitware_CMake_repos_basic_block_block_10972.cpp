(i = 0; i < 3; i++) {
		if (zip->sub_stream_buff[i] != NULL)
			free(zip->sub_stream_buff[i]);
		zip->sub_stream_buff[i] = NULL;
	}