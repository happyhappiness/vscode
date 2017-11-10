static inline int group_next(xdfile_t *xdf, struct xdlgroup *g)
{
	if (g->end == xdf->nrec)
		return -1;

	g->start = g->end + 1;
	for (g->end = g->start; xdf->rchg[g->end]; g->end++)
		;

	return 0;
}