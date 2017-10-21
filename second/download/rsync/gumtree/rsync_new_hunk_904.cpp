			return -1; /* impossible... */
		}
	}

	return -1;
}

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
			new_size += incr;
		else
			new_size *= 2;
		new_ptr = realloc_array(lp->items, char, new_size * item_size);
		if (verbose >= 4) {
			rprintf(FINFO, "[%s] expand %s to %.0f bytes, did%s move\n",
				who_am_i(), desc, (double)new_size * item_size,
				new_ptr == lp->items ? " not" : "");
		}
		if (!new_ptr)
			out_of_memory("expand_item_list");

		lp->items = new_ptr;
		lp->malloced = new_size;
	}
	return (char*)lp->items + (lp->count++ * item_size);
}
