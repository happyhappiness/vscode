
static void show_parents(struct commit *commit, int abbrev)
{
	struct commit_list *p;
	for (p = commit->parents; p ; p = p->next) {
		struct commit *parent = p->item;
		printf(" %s", find_unique_abbrev(parent->object.sha1, abbrev));
	}
}

static void show_children(struct rev_info *opt, struct commit *commit, int abbrev)
{
	struct commit_list *p = lookup_decoration(&opt->children, &commit->object);
	for ( ; p; p = p->next) {
		printf(" %s", find_unique_abbrev(p->item->object.sha1, abbrev));
	}
}

/*
 * Do we have HEAD in the output, and also the branch it points at?
 * If so, find that decoration entry for that current branch.
