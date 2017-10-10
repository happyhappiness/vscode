#undef DIGIT_SIZE
}

/*
 * Ordered list of offsets of objects in the pack.
 */
static void create_pack_revindex(struct pack_revindex *rix)
{
	struct packed_git *p = rix->p;
	unsigned num_ent = p->num_objects;
	unsigned i;
	const char *index = p->index_data;

	ALLOC_ARRAY(rix->revindex, num_ent + 1);
	index += 4 * 256;

	if (p->index_version > 1) {
		const uint32_t *off_32 =
			(uint32_t *)(index + 8 + p->num_objects * (20 + 4));
		const uint32_t *off_64 = off_32 + p->num_objects;
		for (i = 0; i < num_ent; i++) {
			uint32_t off = ntohl(*off_32++);
			if (!(off & 0x80000000)) {
				rix->revindex[i].offset = off;
			} else {
				rix->revindex[i].offset =
					((uint64_t)ntohl(*off_64++)) << 32;
				rix->revindex[i].offset |=
					ntohl(*off_64++);
			}
			rix->revindex[i].nr = i;
		}
	} else {
		for (i = 0; i < num_ent; i++) {
			uint32_t hl = *((uint32_t *)(index + 24 * i));
			rix->revindex[i].offset = ntohl(hl);
			rix->revindex[i].nr = i;
		}
	}

	/* This knows the pack format -- the 20-byte trailer
	 * follows immediately after the last object data.
	 */
	rix->revindex[num_ent].offset = p->pack_size - 20;
	rix->revindex[num_ent].nr = -1;
	sort_revindex(rix->revindex, num_ent, p->pack_size);
}

struct pack_revindex *revindex_for_pack(struct packed_git *p)
{
	int num;
	struct pack_revindex *rix;

	if (!pack_revindex_hashsz)
		init_pack_revindex();

	num = pack_revindex_ix(p);
	if (num < 0)
		die("internal error: pack revindex fubar");

	rix = &pack_revindex[num];
	if (!rix->revindex)
		create_pack_revindex(rix);

	return rix;
}

int find_revindex_position(struct pack_revindex *pridx, off_t ofs)
{
	int lo = 0;
	int hi = pridx->p->num_objects + 1;
	struct revindex_entry *revindex = pridx->revindex;

	do {
		unsigned mi = lo + (hi - lo) / 2;
		if (revindex[mi].offset == ofs) {
			return mi;
		} else if (ofs < revindex[mi].offset)
