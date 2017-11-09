static int update_local_ref(struct ref *ref,
			    const char *remote,
			    const struct ref *remote_ref,
			    struct strbuf *display,
			    int summary_width)
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
			format_display(display, '=', _("[up to date]"), NULL,
				       remote, pretty_ref, summary_width);
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
		format_display(display, '!', _("[rejected]"),
			       _("can't fetch in current branch"),
			       remote, pretty_ref, summary_width);
		return 1;
	}

	if (!is_null_oid(&ref->old_oid) &&
	    starts_with(ref->name, "refs/tags/")) {
		int r;
		r = s_update_ref("updating tag", ref, 0);
		format_display(display, r ? '!' : 't', _("[tag update]"),
			       r ? _("unable to update local ref") : NULL,
			       remote, pretty_ref, summary_width);
		return r;
	}

	current = lookup_commit_reference_gently(&ref->old_oid, 1);
	updated = lookup_commit_reference_gently(&ref->new_oid, 1);
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
			check_for_new_submodule_commits(&ref->new_oid);
		r = s_update_ref(msg, ref, 0);
		format_display(display, r ? '!' : '*', what,
			       r ? _("unable to update local ref") : NULL,
			       remote, pretty_ref, summary_width);
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
			check_for_new_submodule_commits(&ref->new_oid);
		r = s_update_ref("fast-forward", ref, 1);
		format_display(display, r ? '!' : ' ', quickref.buf,
			       r ? _("unable to update local ref") : NULL,
			       remote, pretty_ref, summary_width);
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
			check_for_new_submodule_commits(&ref->new_oid);
		r = s_update_ref("forced-update", ref, 1);
		format_display(display, r ? '!' : '+', quickref.buf,
			       r ? _("unable to update local ref") : _("forced update"),
			       remote, pretty_ref, summary_width);
		strbuf_release(&quickref);
		return r;
	} else {
		format_display(display, '!', _("[rejected]"), _("non-fast-forward"),
			       remote, pretty_ref, summary_width);
		return 1;
	}
}