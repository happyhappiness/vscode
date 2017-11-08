static char *string_area_malloc(struct string_area **ap, int size)
{
	char *p;
	struct string_area *a;

	/* does the request fit into the current space? */
	a = *ap;
	if (a->current + size >= a->end) {
		/* no; get space, move new string_area to front of the list */
		a = string_area_new(size > ARENA_SIZE ? size : ARENA_SIZE);
		a->next = *ap;
		*ap = a;
	}

	/* have space; do the "allocation." */
	p = a->current;
	a->current += size;
	return p;
}