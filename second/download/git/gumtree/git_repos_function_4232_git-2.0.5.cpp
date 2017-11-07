static int branch_merged(int kind, const char *name,
			 struct commit *rev, struct commit *head_rev)
{
	/*
	 * This checks whether the merge bases of branch and HEAD (or
	 * the other branch this branch builds upon) contains the
	 * branch, which means that the branch has already been merged
	 * safely to HEAD (or the other branch).
	 */
	struct commit *reference_rev = NULL;
	const char *reference_name = NULL;
	void *reference_name_to_free = NULL;
	int merged;

	if (kind == REF_LOCAL_BRANCH) {
		struct branch *branch = branch_get(name);
		unsigned char sha1[20];

		if (branch &&
		    branch->merge &&
		    branch->merge[0] &&
		    branch->merge[0]->dst &&
		    (reference_name = reference_name_to_free =
		     resolve_refdup(branch->merge[0]->dst, sha1, 1, NULL)) != NULL)
			reference_rev = lookup_commit_reference(sha1);
	}
	if (!reference_rev)
		reference_rev = head_rev;

	merged = in_merge_bases(rev, reference_rev);

	/*
	 * After the safety valve is fully redefined to "check with
	 * upstream, if any, otherwise with HEAD", we should just
	 * return the result of the in_merge_bases() above without
	 * any of the following code, but during the transition period,
	 * a gentle reminder is in order.
	 */
	if ((head_rev != reference_rev) &&
	    in_merge_bases(rev, head_rev) != merged) {
		if (merged)
			warning(_("deleting branch '%s' that has been merged to\n"
				"         '%s', but not yet merged to HEAD."),
				name, reference_name);
		else
			warning(_("not deleting branch '%s' that is not yet merged to\n"
				"         '%s', even though it is merged to HEAD."),
				name, reference_name);
	}
	free(reference_name_to_free);
	return merged;
}