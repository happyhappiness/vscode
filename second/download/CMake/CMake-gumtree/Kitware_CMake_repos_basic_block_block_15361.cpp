{
		/* Count up the number of empty files. */
		zip->total_number_empty_entry++;
		if (file->dir)
			zip->total_number_dir_entry++;
		else
			file_register_empty(zip, file);
		return (r);
	}