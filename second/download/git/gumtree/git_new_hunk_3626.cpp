	type = sha1_object_info(ref->new_oid.hash, NULL);
	if (type < 0)
		die(_("object %s not found"), oid_to_hex(&ref->new_oid));

	if (!oidcmp(&ref->old_oid, &ref->new_oid)) {
		if (verbosity > 0)
			format_display(display, '=', _("[up to date]"), NULL,
				       remote, pretty_ref);
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
			       remote, pretty_ref);
		return 1;
	}

	if (!is_null_oid(&ref->old_oid) &&
	    starts_with(ref->name, "refs/tags/")) {
		int r;
		r = s_update_ref("updating tag", ref, 0);
		format_display(display, r ? '!' : 't', _("[tag update]"),
			       r ? _("unable to update local ref") : NULL,
			       remote, pretty_ref);
		return r;
	}

	current = lookup_commit_reference_gently(ref->old_oid.hash, 1);
	updated = lookup_commit_reference_gently(ref->new_oid.hash, 1);
	if (!current || !updated) {
