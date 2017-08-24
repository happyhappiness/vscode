(m = list->unmatched_next; m != NULL; m = m->next) {
		int r;

		if (m->matches)
			continue;
		if (mbs) {
			const char *p;
			r = archive_mstring_get_mbs(&(a->archive),
				&(m->pattern), &p);
			if (r < 0 && errno == ENOMEM)
				return (error_nomem(a));
			if (p == NULL)
				p = "";
			*vp = p;
		} else {
			const wchar_t *p;
			r = archive_mstring_get_wcs(&(a->archive),
				&(m->pattern), &p);
			if (r < 0 && errno == ENOMEM)
				return (error_nomem(a));
			if (p == NULL)
				p = L"";
			*vp = p;
		}
		list->unmatched_next = m->next;
		if (list->unmatched_next == NULL)
			/* To return EOF next time. */
			list->unmatched_eof = 1;
		return (ARCHIVE_OK);
	}