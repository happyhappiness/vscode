{
		file_next = file->next;
		file_free(file);
		file = file_next;
	}