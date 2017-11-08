static struct commit_list *first_scapegoat(struct rev_info *revs, struct commit *commit)
{
	if (!reverse) {
		if (revs->first_parent_only &&
		    commit->parents &&
		    commit->parents->next) {
			free_commit_list(commit->parents->next);
			commit->parents->next = NULL;
		}
		return commit->parents;
	}
	return lookup_decoration(&revs->children, &commit->object);
}