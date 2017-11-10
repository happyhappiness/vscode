static struct pack_list * add_pack(struct packed_git *p)
{
	struct pack_list l;
	unsigned long off = 0, step;
	const unsigned char *base;

	if (!p->pack_local && !(alt_odb || verbose))
		return NULL;

	l.pack = p;
	llist_init(&l.all_objects);

	if (open_pack_index(p))
		return NULL;

	base = p->index_data;
	base += 256 * 4 + ((p->index_version < 2) ? 4 : 8);
	step = (p->index_version < 2) ? 24 : 20;
	while (off < p->num_objects * step) {
		llist_insert_back(l.all_objects, base + off);
		off += step;
	}
	/* this list will be pruned in cmp_two_packs later */
	l.unique_objects = llist_copy(l.all_objects);
	if (p->pack_local)
		return pack_list_insert(&local_packs, &l);
	else
		return pack_list_insert(&altodb_packs, &l);
}