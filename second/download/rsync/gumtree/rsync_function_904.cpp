void flist_ndx_push(flist_ndx_list *lp, int ndx)
{
	struct flist_ndx_item *item;

	if (!(item = new(struct flist_ndx_item)))
		out_of_memory("flist_ndx_push");
	item->next = NULL;
	item->ndx = ndx;
	if (lp->tail)
		lp->tail->next = item;
	else
		lp->head = item;
	lp->tail = item;
}