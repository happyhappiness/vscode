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
			hi = mi;
		else
			lo = mi + 1;
	} while (lo < hi);

	error("bad offset for revindex");
	return -1;
}