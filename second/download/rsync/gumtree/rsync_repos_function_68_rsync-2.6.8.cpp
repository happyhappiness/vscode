static struct idlist *recv_add_gid(int id, char *name)
{
	int id2 = name ? map_gid(id, name) : id;
	struct idlist *node;

	if (!am_root && !is_in_group(id2))
		id2 = GID_NONE;
	node = add_to_list(&gidlist, id, name, id2);

	if (verbose > 3) {
		rprintf(FINFO, "gid %d(%s) maps to %d\n",
		    id, name ? name : "", id2);
	}

	return node;
}