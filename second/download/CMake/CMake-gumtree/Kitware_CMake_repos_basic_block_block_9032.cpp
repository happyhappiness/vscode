(archive_mstring_get_mbs(&(a->archive), &(m->pattern), &p)
		    < 0 && errno == ENOMEM)
			return (error_nomem(a));