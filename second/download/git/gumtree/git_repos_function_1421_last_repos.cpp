static int build_fake_ancestor(struct apply_state *state, struct patch *list)
{
	struct patch *patch;
	struct index_state result = { NULL };
	static struct lock_file lock;
	int res;

	/* Once we start supporting the reverse patch, it may be
	 * worth showing the new sha1 prefix, but until then...
	 */
	for (patch = list; patch; patch = patch->next) {
		struct object_id oid;
		struct cache_entry *ce;
		const char *name;

		name = patch->old_name ? patch->old_name : patch->new_name;
		if (0 < patch->is_new)
			continue;

		if (S_ISGITLINK(patch->old_mode)) {
			if (!preimage_oid_in_gitlink_patch(patch, &oid))
				; /* ok, the textual part looks sane */
			else
				return error(_("sha1 information is lacking or "
					       "useless for submodule %s"), name);
		} else if (!get_sha1_blob(patch->old_sha1_prefix, oid.hash)) {
			; /* ok */
		} else if (!patch->lines_added && !patch->lines_deleted) {
			/* mode-only change: update the current */
			if (get_current_oid(state, patch->old_name, &oid))
				return error(_("mode change for %s, which is not "
					       "in current HEAD"), name);
		} else
			return error(_("sha1 information is lacking or useless "
				       "(%s)."), name);

		ce = make_cache_entry(patch->old_mode, oid.hash, name, 0, 0);
		if (!ce)
			return error(_("make_cache_entry failed for path '%s'"),
				     name);
		if (add_index_entry(&result, ce, ADD_CACHE_OK_TO_ADD)) {
			free(ce);
			return error(_("could not add %s to temporary index"),
				     name);
		}
	}

	hold_lock_file_for_update(&lock, state->fake_ancestor, LOCK_DIE_ON_ERROR);
	res = write_locked_index(&result, &lock, COMMIT_LOCK);
	discard_index(&result);

	if (res)
		return error(_("could not write temporary index to %s"),
			     state->fake_ancestor);

	return 0;
}