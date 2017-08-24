{
		sp = entry->sparse_head->next;
		free(entry->sparse_head);
		entry->sparse_head = sp;
	}