static void add_one_tree(const unsigned char *sha1, struct rev_info *revs)
{
	struct tree *tree = lookup_tree(sha1);
	if (tree)
		add_pending_object(revs, &tree->object, "");
}