static void create_pack_revindex(struct pack_revindex *rix)
{
	struct packed_git *p = rix->p;
	unsigned num_ent = p->num_objects;
	unsigned i;
	const char *index = p->index_data;

	rix->revindex = xmalloc(sizeof(*rix->revindex) * (num_ent + 1));
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