{
		q = p;
		p = p->next;
		archive_mstring_clean(&(q->pattern));
		free(q);
	}