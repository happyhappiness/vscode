static int xdl_append_merge(xdmerge_t **merge, int mode,
			    long i0, long chg0,
			    long i1, long chg1,
			    long i2, long chg2)
{
	xdmerge_t *m = *merge;
	if (m && (i1 <= m->i1 + m->chg1 || i2 <= m->i2 + m->chg2)) {
		if (mode != m->mode)
			m->mode = 0;
		m->chg0 = i0 + chg0 - m->i0;
		m->chg1 = i1 + chg1 - m->i1;
		m->chg2 = i2 + chg2 - m->i2;
	} else {
		m = xdl_malloc(sizeof(xdmerge_t));
		if (!m)
			return -1;
		m->next = NULL;
		m->mode = mode;
		m->i0 = i0;
		m->chg0 = chg0;
		m->i1 = i1;
		m->chg1 = chg1;
		m->i2 = i2;
		m->chg2 = chg2;
		if (*merge)
			(*merge)->next = m;
		*merge = m;
	}
	return 0;
}