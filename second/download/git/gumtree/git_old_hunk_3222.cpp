	error("bad offset for revindex");
	return -1;
}

struct revindex_entry *find_pack_revindex(struct packed_git *p, off_t ofs)
{
	struct pack_revindex *pridx = revindex_for_pack(p);
	int pos = find_revindex_position(pridx, ofs);

	if (pos < 0)
		return NULL;

	return pridx->revindex + pos;
}
