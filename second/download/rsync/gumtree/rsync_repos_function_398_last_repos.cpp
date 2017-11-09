void *expand_item_list(item_list *lp, size_t item_size,
		       const char *desc, int incr)
{
	/* First time through, 0 <= 0, so list is expanded. */
	if (lp->malloced <= lp->count) {
		void *new_ptr;
		size_t new_size = lp->malloced;
		if (incr < 0)
			new_size += -incr; /* increase slowly */
		else if (new_size < (size_t)incr)
			new_size = incr;
		else if (new_size)
			new_size *= 2;
		else
			new_size = 1;
		if (new_size <= lp->malloced)
			overflow_exit("expand_item_list");
		/* Using _realloc_array() lets us pass the size, not a type. */
		new_ptr = _realloc_array(lp->items, item_size, new_size);
		if (DEBUG_GTE(FLIST, 3)) {
			rprintf(FINFO, "[%s] expand %s to %s bytes, did%s move\n",
				who_am_i(), desc, big_num(new_size * item_size),
				new_ptr == lp->items ? " not" : "");
		}
		if (!new_ptr)
			out_of_memory("expand_item_list");

		lp->items = new_ptr;
		lp->malloced = new_size;
	}
	return (char*)lp->items + (lp->count++ * item_size);
}