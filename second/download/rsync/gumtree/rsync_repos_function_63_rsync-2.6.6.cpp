static struct idlist *recv_add_uid(int id, char *name)
{
	int id2 = name ? map_uid(id, name) : id;
	struct idlist *node;

	node = add_to_list(&uidlist, id, name, id2);

	if (verbose > 3) {
		rprintf(FINFO, "uid %d(%s) maps to %d\n",
		    id, name ? name : "", id2);
	}

	return node;
}