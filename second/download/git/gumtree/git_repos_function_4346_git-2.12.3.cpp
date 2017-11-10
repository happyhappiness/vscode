static void update_shallow(struct fetch_pack_args *args,
			   struct ref **sought, int nr_sought,
			   struct shallow_info *si)
{
	struct sha1_array ref = SHA1_ARRAY_INIT;
	int *status;
	int i;

	if (args->deepen && alternate_shallow_file) {
		if (*alternate_shallow_file == '\0') { /* --unshallow */
			unlink_or_warn(git_path_shallow());
			rollback_lock_file(&shallow_lock);
		} else
			commit_lock_file(&shallow_lock);
		return;
	}

	if (!si->shallow || !si->shallow->nr)
		return;

	if (args->cloning) {
		/*
		 * remote is shallow, but this is a clone, there are
		 * no objects in repo to worry about. Accept any
		 * shallow points that exist in the pack (iow in repo
		 * after get_pack() and reprepare_packed_git())
		 */
		struct sha1_array extra = SHA1_ARRAY_INIT;
		unsigned char (*sha1)[20] = si->shallow->sha1;
		for (i = 0; i < si->shallow->nr; i++)
			if (has_sha1_file(sha1[i]))
				sha1_array_append(&extra, sha1[i]);
		if (extra.nr) {
			setup_alternate_shallow(&shallow_lock,
						&alternate_shallow_file,
						&extra);
			commit_lock_file(&shallow_lock);
		}
		sha1_array_clear(&extra);
		return;
	}

	if (!si->nr_ours && !si->nr_theirs)
		return;

	remove_nonexistent_theirs_shallow(si);
	if (!si->nr_ours && !si->nr_theirs)
		return;
	for (i = 0; i < nr_sought; i++)
		sha1_array_append(&ref, sought[i]->old_oid.hash);
	si->ref = &ref;

	if (args->update_shallow) {
		/*
		 * remote is also shallow, .git/shallow may be updated
		 * so all refs can be accepted. Make sure we only add
		 * shallow roots that are actually reachable from new
		 * refs.
		 */
		struct sha1_array extra = SHA1_ARRAY_INIT;
		unsigned char (*sha1)[20] = si->shallow->sha1;
		assign_shallow_commits_to_refs(si, NULL, NULL);
		if (!si->nr_ours && !si->nr_theirs) {
			sha1_array_clear(&ref);
			return;
		}
		for (i = 0; i < si->nr_ours; i++)
			sha1_array_append(&extra, sha1[si->ours[i]]);
		for (i = 0; i < si->nr_theirs; i++)
			sha1_array_append(&extra, sha1[si->theirs[i]]);
		setup_alternate_shallow(&shallow_lock,
					&alternate_shallow_file,
					&extra);
		commit_lock_file(&shallow_lock);
		sha1_array_clear(&extra);
		sha1_array_clear(&ref);
		return;
	}

	/*
	 * remote is also shallow, check what ref is safe to update
	 * without updating .git/shallow
	 */
	status = xcalloc(nr_sought, sizeof(*status));
	assign_shallow_commits_to_refs(si, NULL, status);
	if (si->nr_ours || si->nr_theirs) {
		for (i = 0; i < nr_sought; i++)
			if (status[i])
				sought[i]->status = REF_STATUS_REJECT_SHALLOW;
	}
	free(status);
	sha1_array_clear(&ref);
}