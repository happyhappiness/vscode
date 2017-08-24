{
		q = p->next;
		free(p->name);
		free_options(p->options);
		free(p);
		p = q;
	}