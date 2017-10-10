	 * cause the worktree to become inconsistent with HEAD, so allow it.
	 */
	clobber_head_ok = !strcmp(oldname, newname);

	validate_new_branchname(newname, &newref, force, clobber_head_ok);

	reject_rebase_or_bisect_branch(oldref.buf);

	strbuf_addf(&logmsg, "Branch: renamed %s to %s",
		 oldref.buf, newref.buf);

	if (rename_ref(oldref.buf, newref.buf, logmsg.buf))
		die(_("Branch rename failed"));
	strbuf_release(&logmsg);
