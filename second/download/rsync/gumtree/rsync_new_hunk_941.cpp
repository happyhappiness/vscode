		}
	}

	return -1;
}

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

int flist_ndx_pop(flist_ndx_list *lp)
{
	struct flist_ndx_item *next;
	int ndx;

	if (!lp->head)
		return -1;

	ndx = lp->head->ndx;
	next = lp->head->next;
	free(lp->head);
	lp->head = next;
	if (!next)
		lp->tail = NULL;

	return ndx;
}

void *expand_item_list(item_list *lp, size_t item_size,
		       const char *desc, int incr)
{
	/* First time through, 0 <= 0, so list is expanded. */
	if (lp->malloced <= lp->count) {
		void *new_ptr;
