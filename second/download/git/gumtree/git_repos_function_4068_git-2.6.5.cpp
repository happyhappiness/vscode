static void xdl_merge_two_conflicts(xdmerge_t *m)
{
	xdmerge_t *next_m = m->next;
	m->chg1 = next_m->i1 + next_m->chg1 - m->i1;
	m->chg2 = next_m->i2 + next_m->chg2 - m->i2;
	m->next = next_m->next;
	free(next_m);
}