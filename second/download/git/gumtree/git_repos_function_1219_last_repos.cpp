static int rev_compare_tree(struct rev_info *revs,
			    struct commit *parent, struct commit *commit)
{
	struct tree *t1 = parent->tree;
	struct tree *t2 = commit->tree;

	if (!t1)
		return REV_TREE_NEW;
	if (!t2)
		return REV_TREE_OLD;

	if (revs->simplify_by_decoration) {
		/*
		 * If we are simplifying by decoration, then the commit
		 * is worth showing if it has a tag pointing at it.
		 */
		if (get_name_decoration(&commit->object))
			return REV_TREE_DIFFERENT;
		/*
		 * A commit that is not pointed by a tag is uninteresting
		 * if we are not limited by path.  This means that you will
		 * see the usual "commits that touch the paths" plus any
		 * tagged commit by specifying both --simplify-by-decoration
		 * and pathspec.
		 */
		if (!revs->prune_data.nr)
			return REV_TREE_SAME;
	}

	tree_difference = REV_TREE_SAME;
	DIFF_OPT_CLR(&revs->pruning, HAS_CHANGES);
	if (diff_tree_oid(&t1->object.oid, &t2->object.oid, "",
			   &revs->pruning) < 0)
		return REV_TREE_DIFFERENT;
	return tree_difference;
}