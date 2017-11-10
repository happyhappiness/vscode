static int update_local_ref(struct ref *ref,
			    const char *remote,
			    const struct ref *remote_ref,
			    struct strbuf *display)
{
	struct commit *current = NULL, *updated;
	enum object_type type;
	struct branch *current_branch = branch_get(NULL);
	const char *pretty_ref = prettify_refname(ref->name);

	type = sha1_object_info(ref->new_oid.hash, NULL);
	if (type < 0)
		die(_("object %s not found"), oid_to_hex(&ref->new_oid));

	if (!oidcmp(&ref->old_oid, &ref->new_oid)) {
		if (verbosity > 0)
			strbuf_addf(display, "= %-*s %-*s -> %s",
				    TRANSPORT_SUMMARY(_("[up to date]")),
				    REFCOL_WIDTH, remote, pretty_ref);
		return 0;
	}

	if (current_branch &&
	    !strcmp(ref->name, current_branch->name) &&
	    !(update_head_ok || is_bare_repository()) &&
	    !is_null_oid(&ref->old_oid)) {
		/*
		 * If this is the head, and it's not okay to update
		 * the head, and the old value of the head isn't empty...
		 */
		strbuf_addf(display,
			    _("! %-*s %-*s -> %s  (can't fetch in current branch)"),
			    TRANSPORT_SUMMARY(_("[rejected]")),
			    REFCOL_WIDTH, remote, pretty_ref);
		return 1;
	}

	if (!is_null_oid(&ref->old_oid) &&
	    starts_with(ref->name, "refs/tags/")) {
		int r;
		r = s_update_ref("updating tag", ref, 0);
		strbuf_addf(display, "%c %-*s %-*s -> %s%s",
			    r ? '!' : '-',
			    TRANSPORT_SUMMARY(_("[tag update]")),
			    REFCOL_WIDTH, remote, pretty_ref,
			    r ? _("  (unable to update local ref)") : "");
		return r;
	}

	current = lookup_commit_reference_gently(ref->old_oid.hash, 1);
	updated = lookup_commit_reference_gently(ref->new_oid.hash, 1);
	if (!current || !updated) {
		const char *msg;
		const char *what;
		int r;
		/*
		 * Nicely describe the new ref we're fetching.
		 * Base this on the remote's ref name, as it's
		 * more likely to follow a standard layout.
		 */
		const char *name = remote_ref ? remote_ref->name : "";
		if (starts_with(name, "refs/tags/")) {
			msg = "storing tag";
			what = _("[new tag]");
		} else if (starts_with(name, "refs/heads/")) {
			msg = "storing head";
			what = _("[new branch]");
		} else {
			msg = "storing ref";
			what = _("[new ref]");
		}

		if ((recurse_submodules != RECURSE_SUBMODULES_OFF) &&
		    (recurse_submodules != RECURSE_SUBMODULES_ON))
			check_for_new_submodule_commits(ref->new_oid.hash);
		r = s_update_ref(msg, ref, 0);
		strbuf_addf(display, "%c %-*s %-*s -> %s%s",
			    r ? '!' : '*',
			    TRANSPORT_SUMMARY(what),
			    REFCOL_WIDTH, remote, pretty_ref,
			    r ? _("  (unable to update local ref)") : "");
		return r;
	}

	if (in_merge_bases(current, updated)) {
		struct strbuf quickref = STRBUF_INIT;
		int r;
		strbuf_add_unique_abbrev(&quickref, current->object.oid.hash, DEFAULT_ABBREV);
		strbuf_addstr(&quickref, "..");
		strbuf_add_unique_abbrev(&quickref, ref->new_oid.hash, DEFAULT_ABBREV);
		if ((recurse_submodules != RECURSE_SUBMODULES_OFF) &&
		    (recurse_submodules != RECURSE_SUBMODULES_ON))
			check_for_new_submodule_commits(ref->new_oid.hash);
		r = s_update_ref("fast-forward", ref, 1);
		strbuf_addf(display, "%c %-*s %-*s -> %s%s",
			    r ? '!' : ' ',
			    TRANSPORT_SUMMARY_WIDTH, quickref.buf,
			    REFCOL_WIDTH, remote, pretty_ref,
			    r ? _("  (unable to update local ref)") : "");
		strbuf_release(&quickref);
		return r;
	} else if (force || ref->force) {
		struct strbuf quickref = STRBUF_INIT;
		int r;
		strbuf_add_unique_abbrev(&quickref, current->object.oid.hash, DEFAULT_ABBREV);
		strbuf_addstr(&quickref, "...");
		strbuf_add_unique_abbrev(&quickref, ref->new_oid.hash, DEFAULT_ABBREV);
		if ((recurse_submodules != RECURSE_SUBMODULES_OFF) &&
		    (recurse_submodules != RECURSE_SUBMODULES_ON))
			check_for_new_submodule_commits(ref->new_oid.hash);
		r = s_update_ref("forced-update", ref, 1);
		strbuf_addf(display, "%c %-*s %-*s -> %s  (%s)",
			    r ? '!' : '+',
			    TRANSPORT_SUMMARY_WIDTH, quickref.buf,
			    REFCOL_WIDTH, remote, pretty_ref,
			    r ? _("unable to update local ref") : _("forced update"));
		strbuf_release(&quickref);
		return r;
	} else {
		strbuf_addf(display, "! %-*s %-*s -> %s  %s",
			    TRANSPORT_SUMMARY(_("[rejected]")),
			    REFCOL_WIDTH, remote, pretty_ref,
			    _("(non-fast-forward)"));
		return 1;
	}
}