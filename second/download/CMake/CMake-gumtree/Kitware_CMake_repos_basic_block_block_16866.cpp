{
		file_next = file->next;
		mtree_entry_free(file);
		file = file_next;
	}