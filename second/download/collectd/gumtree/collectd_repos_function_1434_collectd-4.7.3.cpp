static inline int
match_different(const STRUCT_ENTRY_MATCH *a,
		const unsigned char *a_elems,
		const unsigned char *b_elems,
		unsigned char **maskptr)
{
	const STRUCT_ENTRY_MATCH *b;
	unsigned int i;

	/* Offset of b is the same as a. */
	b = (void *)b_elems + ((unsigned char *)a - a_elems);

	if (a->u.match_size != b->u.match_size)
		return 1;

	if (strcmp(a->u.user.name, b->u.user.name) != 0)
		return 1;

	*maskptr += ALIGN(sizeof(*a));

	for (i = 0; i < a->u.match_size - ALIGN(sizeof(*a)); i++)
		if (((a->data[i] ^ b->data[i]) & (*maskptr)[i]) != 0)
			return 1;
	*maskptr += i;
	return 0;
}