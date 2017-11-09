static unsigned char determine_fanout(struct int_node *tree, unsigned char n,
		unsigned char fanout)
{
	/*
	 * The following is a simple heuristic that works well in practice:
	 * For each even-numbered 16-tree level (remember that each on-disk
	 * fanout level corresponds to _two_ 16-tree levels), peek at all 16
	 * entries at that tree level. If all of them are either int_nodes or
	 * subtree entries, then there are likely plenty of notes below this
	 * level, so we return an incremented fanout.
	 */
	unsigned int i;
	if ((n % 2) || (n > 2 * fanout))
		return fanout;
	for (i = 0; i < 16; i++) {
		switch (GET_PTR_TYPE(tree->a[i])) {
		case PTR_TYPE_SUBTREE:
		case PTR_TYPE_INTERNAL:
			continue;
		default:
			return fanout;
		}
	}
	return fanout + 1;
}