{
			const char *p;
			r = archive_mstring_get_mbs(&(a->archive),
				&(m->pattern), &p);
			if (r < 0 && errno == ENOMEM)
				return (error_nomem(a));
			if (p == NULL)
				p = "";
			*vp = p;
		}