static int group_slide_up(xdfile_t *xdf, struct xdlgroup *g, long flags)
{
	if (g->start > 0 &&
	    recs_match(xdf->recs[g->start - 1], xdf->recs[g->end - 1], flags)) {
		xdf->rchg[--g->start] = 1;
		xdf->rchg[--g->end] = 0;

		while (xdf->rchg[g->start - 1])
			g->start--;

		return 0;
	} else {
		return -1;
	}
}