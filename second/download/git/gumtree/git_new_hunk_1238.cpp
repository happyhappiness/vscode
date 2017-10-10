}

static int check_branch_commit(const char *branchname, const char *refname,
			       const struct object_id *oid, struct commit *head_rev,
			       int kinds, int force)
{
	struct commit *rev = lookup_commit_reference(oid);
	if (!rev) {
		error(_("Couldn't look up commit object for '%s'"), refname);
		return -1;
	}
	if (!force && !branch_merged(kinds, branchname, rev, head_rev)) {
		error(_("The branch '%s' is not fully merged.\n"
