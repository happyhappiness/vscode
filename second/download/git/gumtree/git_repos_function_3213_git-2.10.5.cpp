static struct tree *shift_tree_object(struct tree *one, struct tree *two,
				      const char *subtree_shift)
{
	struct object_id shifted;

	if (!*subtree_shift) {
		shift_tree(&one->object.oid, &two->object.oid, &shifted, 0);
	} else {
		shift_tree_by(&one->object.oid, &two->object.oid, &shifted,
			      subtree_shift);
	}
	if (!oidcmp(&two->object.oid, &shifted))
		return two;
	return lookup_tree(shifted.hash);
}