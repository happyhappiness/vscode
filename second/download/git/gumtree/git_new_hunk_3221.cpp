#undef DIGIT_SIZE
}

/*
 * Ordered list of offsets of objects in the pack.
 */
static void create_pack_revindex(struct packed_git *p)
{
	unsigned num_ent = p->num_objects;
	unsigned i;
	const char *index = p->index_data;

	ALLOC_ARRAY(p->revindex, num_ent + 1);
	index += 4 * 256;

	if (p->index_version > 1) {
		const uint32_t *off_32 =
			(uint32_t *)(index + 8 + p->num_objects * (20 + 4));
		const uint32_t *off_64 = off_32 + p->num_objects;
		for (i = 0; i < num_ent; i++) {
			uint32_t off = ntohl(*off_32++);
			if (!(off & 0x80000000)) {
				p->revindex[i].offset = off;
			} else {
				p->revindex[i].offset =
					((uint64_t)ntohl(*off_64++)) << 32;
				p->revindex[i].offset |=
					ntohl(*off_64++);
			}
			p->revindex[i].nr = i;
		}
	} else {
		for (i = 0; i < num_ent; i++) {
			uint32_t hl = *((uint32_t *)(index + 24 * i));
			p->revindex[i].offset = ntohl(hl);
			p->revindex[i].nr = i;
		}
	}

	/* This knows the pack format -- the 20-byte trailer
	 * follows immediately after the last object data.
	 */
	p->revindex[num_ent].offset = p->pack_size - 20;
	p->revindex[num_ent].nr = -1;
	sort_revindex(p->revindex, num_ent, p->pack_size);
}

void load_pack_revindex(struct packed_git *p)
{
	if (!p->revindex)
		create_pack_revindex(p);
}

int find_revindex_position(struct packed_git *p, off_t ofs)
{
	int lo = 0;
	int hi = p->num_objects + 1;
	struct revindex_entry *revindex = p->revindex;

	do {
		unsigned mi = lo + (hi - lo) / 2;
		if (revindex[mi].offset == ofs) {
			return mi;
		} else if (ofs < revindex[mi].offset)
