static int num_scapegoats(struct rev_info *revs, struct commit *commit)
{
	int cnt;
	struct commit_list *l = first_scapegoat(revs, commit);
	for (cnt = 0; l; l = l->next)
		cnt++;
	return cnt;
}