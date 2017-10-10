	}
	free(reference_name_to_free);
	return merged;
}

static int check_branch_commit(const char *branchname, const char *refname,
			       unsigned char *sha1, struct commit *head_rev,
			       int kinds, int force)
{
	struct commit *rev = lookup_commit_reference(sha1);
	if (!rev) {
		error(_("Couldn't look up commit object for '%s'"), refname);
		return -1;
