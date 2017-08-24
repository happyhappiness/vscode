(zip->v_data == NULL) {
		zip->v_data = malloc(zip->v_size);
		if (zip->v_data == NULL)
			goto nomem;
	}