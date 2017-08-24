{
		const char *p;
		r = archive_mstring_get_mbs(&(a->archive), &(m->pattern), &p);
		if (r == 0)
			return (archive_pathmatch(p, (const char *)pn, flag));
	}