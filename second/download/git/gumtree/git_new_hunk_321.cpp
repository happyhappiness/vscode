		 !strcmp(active_cache[-1 - pos]->name, path))
		; /* path is in the index, unmerged */
	else
		die("no such path '%s' in HEAD", path);
}

static struct commit_list **append_parent(struct commit_list **tail, const struct object_id *oid)
{
	struct commit *parent;

	parent = lookup_commit_reference(oid->hash);
	if (!parent)
		die("no such commit %s", oid_to_hex(oid));
	return &commit_list_insert(parent, tail)->next;
}

static void append_merge_parents(struct commit_list **tail)
{
	int merge_head;
