static int num_scapegoats(struct rev_info *revs, struct commit *commit)
{
	struct commit_list *l = first_scapegoat(revs, commit);
	return commit_list_count(l);
}