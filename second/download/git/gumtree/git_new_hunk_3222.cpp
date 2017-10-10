	error("bad offset for revindex");
	return -1;
}

struct revindex_entry *find_pack_revindex(struct packed_git *p, off_t ofs)
{
	int pos;

	load_pack_revindex(p);
	pos = find_revindex_position(p, ofs);

	if (pos < 0)
		return NULL;

	return p->revindex + pos;
}
