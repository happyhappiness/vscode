{
		sp = entry->sparse_head;
		if (sp->offset == 0 &&
		    sp->length >= archive_entry_size(entry)) {
			count = 0;
			archive_entry_sparse_clear(entry);
		}
	}