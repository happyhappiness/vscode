		die(_("Branch rename failed"));
	strbuf_release(&logmsg);

	if (recovery)
		warning(_("Renamed a misnamed branch '%s' away"), oldref.buf + 11);

	if (replace_each_worktree_head_symref(oldref.buf, newref.buf))
		die(_("Branch renamed to %s, but HEAD is not updated!"), newname);

	strbuf_addf(&oldsection, "branch.%s", oldref.buf + 11);
	strbuf_release(&oldref);
	strbuf_addf(&newsection, "branch.%s", newref.buf + 11);
	strbuf_release(&newref);
