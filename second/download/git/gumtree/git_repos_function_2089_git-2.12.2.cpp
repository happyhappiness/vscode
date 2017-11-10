off_t find_pack_entry_one(const unsigned char *sha1,
				  struct packed_git *p)
{
	const uint32_t *level1_ofs = p->index_data;
	const unsigned char *index = p->index_data;
	unsigned hi, lo, stride;
	static int use_lookup = -1;
	static int debug_lookup = -1;

	if (debug_lookup < 0)
		debug_lookup = !!getenv("GIT_DEBUG_LOOKUP");

	if (!index) {
		if (open_pack_index(p))
			return 0;
		level1_ofs = p->index_data;
		index = p->index_data;
	}
	if (p->index_version > 1) {
		level1_ofs += 2;
		index += 8;
	}
	index += 4 * 256;
	hi = ntohl(level1_ofs[*sha1]);
	lo = ((*sha1 == 0x0) ? 0 : ntohl(level1_ofs[*sha1 - 1]));
	if (p->index_version > 1) {
		stride = 20;
	} else {
		stride = 24;
		index += 4;
	}

	if (debug_lookup)
		printf("%02x%02x%02x... lo %u hi %u nr %"PRIu32"\n",
		       sha1[0], sha1[1], sha1[2], lo, hi, p->num_objects);

	if (use_lookup < 0)
		use_lookup = !!getenv("GIT_USE_LOOKUP");
	if (use_lookup) {
		int pos = sha1_entry_pos(index, stride, 0,
					 lo, hi, p->num_objects, sha1);
		if (pos < 0)
			return 0;
		return nth_packed_object_offset(p, pos);
	}

	do {
		unsigned mi = (lo + hi) / 2;
		int cmp = hashcmp(index + mi * stride, sha1);

		if (debug_lookup)
			printf("lo %u hi %u rg %u mi %u\n",
			       lo, hi, hi - lo, mi);
		if (!cmp)
			return nth_packed_object_offset(p, mi);
		if (cmp > 0)
			hi = mi;
		else
			lo = mi+1;
	} while (lo < hi);
	return 0;
}