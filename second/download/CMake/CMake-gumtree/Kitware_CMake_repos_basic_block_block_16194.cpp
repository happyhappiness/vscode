{
		file_next = file->allnext;
		isofile_free(file);
		file = file_next;
	}