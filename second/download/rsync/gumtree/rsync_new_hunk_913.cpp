						struct filter_struct *,
						mergelist_size);
			if (!mergelist_parents)
				out_of_memory("add_rule");
		}
		mergelist_parents[mergelist_cnt++] = ret;
	} else
		ret->u.slash_cnt = slash_cnt;

	ret->match_flags = mflags;

	if (!listp->tail) {
		ret->next = listp->head;
		listp->head = listp->tail = ret;
