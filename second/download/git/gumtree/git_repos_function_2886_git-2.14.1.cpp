static int which_parent(const struct object_id *oid, const struct commit *commit)
{
	int nth;
	const struct commit_list *parent;

	for (nth = 0, parent = commit->parents; parent; parent = parent->next) {
		if (!oidcmp(&parent->item->object.oid, oid))
			return nth;
		nth++;
	}
	return -1;
}