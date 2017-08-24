{
		const wchar_t *p;
		r = archive_mstring_get_wcs(&(a->archive), &(m->pattern), &p);
		if (r == 0)
			return (archive_pathmatch_w(p, (const wchar_t *)pn,
				flag));
	}