(zip->erd == NULL) {
		zip->erd = malloc(zip->erd_size);
		if (zip->erd == NULL)
			goto nomem;
	}