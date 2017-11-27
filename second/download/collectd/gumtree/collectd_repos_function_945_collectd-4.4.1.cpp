static unsigned char *
is_same(const STRUCT_ENTRY *a, const STRUCT_ENTRY *b,
	unsigned char *matchmask)
{
	unsigned int i;
	unsigned char *mptr;

	/* Always compare head structures: ignore mask here. */
	if (memcmp(&a->ipv6.src, &b->ipv6.src, sizeof(struct in6_addr))
	    || memcmp(&a->ipv6.dst, &b->ipv6.dst, sizeof(struct in6_addr))
	    || memcmp(&a->ipv6.smsk, &b->ipv6.smsk, sizeof(struct in6_addr))
	    || memcmp(&a->ipv6.dmsk, &b->ipv6.dmsk, sizeof(struct in6_addr))
	    || a->ipv6.proto != b->ipv6.proto
	    || a->ipv6.tos != b->ipv6.tos
	    || a->ipv6.flags != b->ipv6.flags
	    || a->ipv6.invflags != b->ipv6.invflags)
		return NULL;

	for (i = 0; i < IFNAMSIZ; i++) {
		if (a->ipv6.iniface_mask[i] != b->ipv6.iniface_mask[i])
			return NULL;
		if ((a->ipv6.iniface[i] & a->ipv6.iniface_mask[i])
		    != (b->ipv6.iniface[i] & b->ipv6.iniface_mask[i]))
			return NULL;
		if (a->ipv6.outiface_mask[i] != b->ipv6.outiface_mask[i])
			return NULL;
		if ((a->ipv6.outiface[i] & a->ipv6.outiface_mask[i])
		    != (b->ipv6.outiface[i] & b->ipv6.outiface_mask[i]))
			return NULL;
	}

	if (a->target_offset != b->target_offset
	    || a->next_offset != b->next_offset)
		return NULL;

	mptr = matchmask + sizeof(STRUCT_ENTRY);
	if (IP6T_MATCH_ITERATE(a, match_different, a->elems, b->elems, &mptr))
		return NULL;
	mptr += IP6T_ALIGN(sizeof(struct ip6t_entry_target));

	return mptr;
}