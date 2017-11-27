static inline int
target_same(struct rule_head *a, struct rule_head *b,const unsigned char *mask)
{
	unsigned int i;
	STRUCT_ENTRY_TARGET *ta, *tb;

	if (a->type != b->type)
		return 0;

	ta = GET_TARGET(a->entry);
	tb = GET_TARGET(b->entry);

	switch (a->type) {
	case IPTCC_R_FALLTHROUGH:
		return 1;
	case IPTCC_R_JUMP:
		return a->jump == b->jump;
	case IPTCC_R_STANDARD:
		return ((STRUCT_STANDARD_TARGET *)ta)->verdict
			== ((STRUCT_STANDARD_TARGET *)tb)->verdict;
	case IPTCC_R_MODULE:
		if (ta->u.target_size != tb->u.target_size)
			return 0;
		if (strcmp(ta->u.user.name, tb->u.user.name) != 0)
			return 0;

		for (i = 0; i < ta->u.target_size - sizeof(*ta); i++)
			if (((ta->data[i] ^ tb->data[i]) & mask[i]) != 0)
				return 0;
		return 1;
	default:
		fprintf(stderr, "ERROR: bad type %i\n", a->type);
		abort();
	}
}