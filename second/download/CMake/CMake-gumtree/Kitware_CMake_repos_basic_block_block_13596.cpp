(ts < zip->erd_size) {
		free(zip->erd);
		zip->erd = NULL;
	}