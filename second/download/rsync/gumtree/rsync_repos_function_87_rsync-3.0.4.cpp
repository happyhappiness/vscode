static struct idlist *recv_add_gid(gid_t id, const char *name)
{
	gid_t id2 = name ? map_gid(id, name) : id;
	struct idlist *node;

	node = add_to_list(&gidlist, id, name, id2,
		!am_root && !is_in_group(id2) ? FLAG_SKIP_GROUP : 0);

	if (verbose > 3) {
		rprintf(FINFO, "gid %u(%s) maps to %u\n",
			(unsigned)id, name ? name : "", (unsigned)id2);
	}

	return node;
}