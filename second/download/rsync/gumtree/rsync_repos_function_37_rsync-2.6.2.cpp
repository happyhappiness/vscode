void free_exclude_list(struct exclude_list_struct *listp)
{
	struct exclude_struct *ent, *next;

	if (verbose > 2) {
		rprintf(FINFO, "[%s] clearing %sexclude list\n",
			who_am_i(), listp->debug_type);
	}

	for (ent = listp->head; ent; ent = next) {
		next = ent->next;
		free_exclude(ent);
	}

	listp->head = listp->tail = NULL;
}