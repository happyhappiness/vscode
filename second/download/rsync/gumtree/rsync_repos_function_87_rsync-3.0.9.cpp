static struct idlist *recv_add_uid(uid_t id, const char *name)
{
	uid_t id2 = name ? map_uid(id, name) : id;
	struct idlist *node;

	node = add_to_list(&uidlist, id, name, id2, 0);

	if (verbose > 3) {
		rprintf(FINFO, "uid %u(%s) maps to %u\n",
			(unsigned)id, name ? name : "", (unsigned)id2);
	}

	return node;
}