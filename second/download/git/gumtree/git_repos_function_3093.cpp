static struct tree *shift_tree_object(struct tree *one, struct tree *two,
				      const char *subtree_shift)
{
	unsigned char shifted[20];

	if (!*subtree_shift) {
		shift_tree(one->object.sha1, two->object.sha1, shifted, 0);
	} else {
		shift_tree_by(one->object.sha1, two->object.sha1, shifted,
			      subtree_shift);
	}
	if (!hashcmp(two->object.sha1, shifted))
		return two;
	return lookup_tree(shifted);
}