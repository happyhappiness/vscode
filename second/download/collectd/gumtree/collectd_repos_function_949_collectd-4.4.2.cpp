static unsigned char *
is_same(const STRUCT_ENTRY *a, const STRUCT_ENTRY *b, unsigned char *matchmask)
{
	unsigned int i;
	unsigned char *mptr;

	/* Always compare head structures: ignore mask here. */
	if (a->ip.src.s_addr != b->ip.src.s_addr
	    || a->ip.dst.s_addr != b->ip.dst.s_addr
	    || a->ip.smsk.s_addr != b->ip.smsk.s_addr
	    || a->ip.dmsk.s_addr != b->ip.dmsk.s_addr
	    || a->ip.proto != b->ip.proto
	    || a->ip.flags != b->ip.flags
	    || a->ip.invflags != b->ip.invflags)
		return NULL;

	for (i = 0; i < IFNAMSIZ; i++) {
		if (a->ip.iniface_mask[i] != b->ip.iniface_mask[i])
			return NULL;
		if ((a->ip.iniface[i] & a->ip.iniface_mask[i])
		    != (b->ip.iniface[i] & b->ip.iniface_mask[i]))
			return NULL;
		if (a->ip.outiface_mask[i] != b->ip.outiface_mask[i])
			return NULL;
		if ((a->ip.outiface[i] & a->ip.outiface_mask[i])
		    != (b->ip.outiface[i] & b->ip.outiface_mask[i]))
			return NULL;
	}

	if (a->target_offset != b->target_offset
	    || a->next_offset != b->next_offset)
		return NULL;

	mptr = matchmask + sizeof(STRUCT_ENTRY);
	if (IPT_MATCH_ITERATE(a, match_different, a->elems, b->elems, &mptr))
		return NULL;
	mptr += IPT_ALIGN(sizeof(struct ipt_entry_target));

	return mptr;
}