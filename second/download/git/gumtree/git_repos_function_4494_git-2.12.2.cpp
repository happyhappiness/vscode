static void group_init(xdfile_t *xdf, struct xdlgroup *g)
{
	g->start = g->end = 0;
	while (xdf->rchg[g->end])
		g->end++;
}