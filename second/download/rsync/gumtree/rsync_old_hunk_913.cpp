						struct filter_struct *,
						mergelist_size);
			if (!mergelist_parents)
				out_of_memory("add_rule");
		}
		mergelist_parents[mergelist_cnt++] = ret;
	} else {
		for (cp = ret->pattern; (cp = strchr(cp, '/')) != NULL; cp++)
			ret->u.slash_cnt++;
	}

	ret->match_flags = mflags;

	if (!listp->tail) {
		ret->next = listp->head;
		listp->head = listp->tail = ret;
