static struct commit_list *first_scapegoat(struct rev_info *revs, struct commit *commit)
{
	if (!reverse)
		return commit->parents;
	return lookup_decoration(&revs->children, &commit->object);
}