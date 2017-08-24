{
	int flag = PATHMATCH_NO_ANCHOR_START | PATHMATCH_NO_ANCHOR_END;
	int r;

	if (mbs) {
		const char *p;
		r = archive_mstring_get_mbs(&(a->archive), &(m->pattern), &p);
		if (r == 0)
			return (archive_pathmatch(p, (const char *)pn, flag));
	} else {
		const wchar_t *p;
		r = archive_mstring_get_wcs(&(a->archive), &(m->pattern), &p);
		if (r == 0)
			return (archive_pathmatch_w(p, (const wchar_t *)pn,
				flag));
	}
	if (errno == ENOMEM)
		return (error_nomem(a));
	return (0);
}