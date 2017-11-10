static int add_branch_for_removal(const char *refname,
	const struct object_id *oid, int flags, void *cb_data)
{
	struct branches_for_remote *branches = cb_data;
	struct refspec refspec;
	struct known_remote *kr;

	memset(&refspec, 0, sizeof(refspec));
	refspec.dst = (char *)refname;
	if (remote_find_tracking(branches->remote, &refspec))
		return 0;

	/* don't delete a branch if another remote also uses it */
	for (kr = branches->keep->list; kr; kr = kr->next) {
		memset(&refspec, 0, sizeof(refspec));
		refspec.dst = (char *)refname;
		if (!remote_find_tracking(kr->remote, &refspec))
			return 0;
	}

	/* don't delete non-remote-tracking refs */
	if (!starts_with(refname, "refs/remotes/")) {
		/* advise user how to delete local branches */
		if (starts_with(refname, "refs/heads/"))
			string_list_append(branches->skipped,
					   abbrev_branch(refname));
		/* silently skip over other non-remote refs */
		return 0;
	}

	string_list_append(branches->branches, refname);

	return 0;
}