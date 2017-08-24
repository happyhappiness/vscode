{
	struct match *m;
	const wchar_t *p;

	if (name == NULL || *name == L'\0')
		return (0);
	for (m = list->first; m; m = m->next) {
		if (archive_mstring_get_wcs(&(a->archive), &(m->pattern), &p)
		    < 0 && errno == ENOMEM)
			return (error_nomem(a));
		if (p != NULL && wcscmp(p, name) == 0) {
			m->matches++;
			return (1);
		}
	}
	return (0);
}