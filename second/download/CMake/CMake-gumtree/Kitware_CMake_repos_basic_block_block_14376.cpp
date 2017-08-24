{
		struct archive_write_filter *next
		    = a->filter_first->next_filter;
		if (a->filter_first->free != NULL) {
			r1 = (*a->filter_first->free)(a->filter_first);
			if (r > r1)
				r = r1;
		}
		free(a->filter_first);
		a->filter_first = next;
	}