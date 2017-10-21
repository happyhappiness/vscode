		else
			new_size *= 2;
		if (new_size < lp->malloced)
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
