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
