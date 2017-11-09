static struct idlist *recv_add_id(struct idlist **idlist_ptr, struct idlist *idmap,
				  id_t id, const char *name)
{
	struct idlist *node;
	union name_or_id noiu;
	int flag;
	id_t id2;

	noiu.name = name; /* ensure that add_to_list() gets the raw value. */
	if (!name)
		name = "";

	for (node = idmap; node; node = node->next) {
		if (node->flags & NFLAGS_WILD_NAME_MATCH) {
			if (!wildmatch(node->u.name, name))
				continue;
		} else if (node->flags & NFLAGS_NAME_MATCH) {
			if (strcmp(node->u.name, name) != 0)
				continue;
		} else if (node->u.max_id) {
			if (id < node->id || id > node->u.max_id)
				continue;
		} else {
			if (node->id != id)
				continue;
		}
		break;
	}
	if (node)
		id2 = node->id2;
	else if (*name && id) {
		if (idlist_ptr == &uidlist) {
			uid_t uid;
			id2 = user_to_uid(name, &uid, False) ? uid : id;
		} else {
			gid_t gid;
			id2 = group_to_gid(name, &gid, False) ? gid : id;
		}
	} else
		id2 = id;

	flag = idlist_ptr == &gidlist && !am_root && !is_in_group(id2) ? FLAG_SKIP_GROUP : 0;
	node = add_to_list(idlist_ptr, id, noiu, id2, flag);

	if (DEBUG_GTE(OWN, 2)) {
		rprintf(FINFO, "%sid %u(%s) maps to %u\n",
			idlist_ptr == &uidlist ? "u" : "g",
			(unsigned)id, name, (unsigned)id2);
	}

	return node;
}