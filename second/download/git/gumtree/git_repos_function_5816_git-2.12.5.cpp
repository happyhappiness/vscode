static void new_parent(struct commit *parent, struct commit_list **parents_p)
{
	struct object_id *oid = &parent->object.oid;
	struct commit_list *parents;
	for (parents = *parents_p; parents; parents = parents->next) {
		if (parents->item == parent) {
			error("duplicate parent %s ignored", oid_to_hex(oid));
			return;
		}
		parents_p = &parents->next;
	}
	commit_list_insert(parent, parents_p);
}