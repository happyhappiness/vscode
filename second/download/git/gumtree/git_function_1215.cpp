static struct commit_list **append_parent(struct commit_list **tail, const struct object_id *oid)
{
	struct commit *parent;

	parent = lookup_commit_reference(oid->hash);
	if (!parent)
		die("no such commit %s", oid_to_hex(oid));
	return &commit_list_insert(parent, tail)->next;
}