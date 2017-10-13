tatic int delete_branches(int argc, const char **argv, int force, int kinds,
			   int quiet)
{
	struct commit *head_rev = NULL;
	unsigned char sha1[20];
	char *name = NULL;
	const char *fmt;
	int i;
	int ret = 0;
	int remote_branch = 0;
	struct strbuf bname = STRBUF_INIT;

	switch (kinds) {
	case FILTER_REFS_REMOTES:
		fmt = "refs/remotes/%s";
		/* For subsequent UI messages */
		remote_branch = 1;

		force = 1;
		break;
	case FILTER_REFS_BRANCHES:
		fmt = "refs/heads/%s";
		break;
	default:
		die(_("cannot use -a with -d"));
	}

	if (!force) {
		head_rev = lookup_commit_reference(head_sha1);
		if (!head_rev)
			die(_("Couldn't look up commit object for HEAD"));
	}
	for (i = 0; i < argc; i++, strbuf_release(&bname)) {
		const char *target;
		int flags = 0;

		strbuf_branchname(&bname, argv[i]);
		if (kinds == FILTER_REFS_BRANCHES && !strcmp(head, bname.buf)) {
			error(_("Cannot delete the branch '%s' "
			      "which you are currently on."), bname.buf);
			ret = 1;
			continue;
		}

		free(name);

		name = mkpathdup(fmt, bname.buf);
		target = resolve_ref_unsafe(name,
					    RESOLVE_REF_READING
					    | RESOLVE_REF_NO_RECURSE
					    | RESOLVE_REF_ALLOW_BAD_NAME,
					    sha1, &flags);
		if (!target) {
			error(remote_branch
			      ? _("remote-tracking branch '%s' not found.")
			      : _("branch '%s' not found."), bname.buf);
			ret = 1;
			continue;
		}

		if (!(flags & (REF_ISSYMREF|REF_ISBROKEN)) &&
		    check_branch_commit(bname.buf, name, sha1, head_rev, kinds,
					force)) {
			ret = 1;
			continue;
		}

		if (delete_ref(name, is_null_sha1(sha1) ? NULL : sha1,
			       REF_NODEREF)) {
			error(remote_branch
			      ? _("Error deleting remote-tracking branch '%s'")
			      : _("Error deleting branch '%s'"),
			      bname.buf);
			ret = 1;
			continue;
		}
		if (!quiet) {
			printf(remote_branch
			       ? _("Deleted remote-tracking branch %s (was %s).\n")
			       : _("Deleted branch %s (was %s).\n"),
			       bname.buf,
			       (flags & REF_ISBROKEN) ? "broken"
			       : (flags & REF_ISSYMREF) ? target
			       : find_unique_abbrev(sha1, DEFAULT_ABBREV));
		}
		delete_branch_config(bname.buf);
	}

	free(name);

	return(ret);
}