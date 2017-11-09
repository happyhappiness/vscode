static int num_scapegoats(struct rev_info *revs, struct commit *commit, int reverse)
{
	struct commit_list *l = first_scapegoat(revs, commit, reverse);
	return commit_list_count(l);
}