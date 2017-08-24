{
		/* Add a new sparse block to the tail of list. */
		if (entry->sparse_tail != NULL)
			entry->sparse_tail->next = sp;
		entry->sparse_tail = sp;
	}