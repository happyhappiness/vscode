static void show_children(struct rev_info *opt, struct commit *commit, int abbrev)
{
	struct commit_list *p = lookup_decoration(&opt->children, &commit->object);
	for ( ; p; p = p->next) {
		printf(" %s", find_unique_abbrev(p->item->object.oid.hash, abbrev));
	}
}