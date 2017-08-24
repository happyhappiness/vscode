(m = list->first; m; m = m->next) {
		if (archive_mstring_get_mbs(&(a->archive), &(m->pattern), &p)
		    < 0 && errno == ENOMEM)
			return (error_nomem(a));
		if (p != NULL && strcmp(p, name) == 0) {
			m->matches++;
			return (1);
		}
	}