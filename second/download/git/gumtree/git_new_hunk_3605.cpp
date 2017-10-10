	} else if ((errno != ENOENT) && (errno != ENOTDIR)) {
		return error("%s: %s", new_name, strerror(errno));
	}
	return 0;
}

static uintptr_t register_symlink_changes(struct apply_state *state,
					  const char *path,
					  uintptr_t what)
{
	struct string_list_item *ent;

	ent = string_list_lookup(&state->symlink_changes, path);
	if (!ent) {
		ent = string_list_insert(&state->symlink_changes, path);
		ent->util = (void *)0;
	}
	ent->util = (void *)(what | ((uintptr_t)ent->util));
	return (uintptr_t)ent->util;
}

static uintptr_t check_symlink_changes(struct apply_state *state, const char *path)
{
	struct string_list_item *ent;

	ent = string_list_lookup(&state->symlink_changes, path);
	if (!ent)
		return 0;
	return (uintptr_t)ent->util;
}

static void prepare_symlink_changes(struct apply_state *state, struct patch *patch)
{
	for ( ; patch; patch = patch->next) {
		if ((patch->old_name && S_ISLNK(patch->old_mode)) &&
		    (patch->is_rename || patch->is_delete))
			/* the symlink at patch->old_name is removed */
			register_symlink_changes(state, patch->old_name, SYMLINK_GOES_AWAY);

		if (patch->new_name && S_ISLNK(patch->new_mode))
			/* the symlink at patch->new_name is created or remains */
			register_symlink_changes(state, patch->new_name, SYMLINK_IN_RESULT);
	}
}

static int path_is_beyond_symlink_1(struct apply_state *state, struct strbuf *name)
{
	do {
		unsigned int change;

		while (--name->len && name->buf[name->len] != '/')
			; /* scan backwards */
		if (!name->len)
			break;
		name->buf[name->len] = '\0';
		change = check_symlink_changes(state, name->buf);
		if (change & SYMLINK_IN_RESULT)
			return 1;
		if (change & SYMLINK_GOES_AWAY)
			/*
			 * This cannot be "return 0", because we may
			 * see a new one created at a higher level.
			 */
			continue;

		/* otherwise, check the preimage */
		if (state->check_index) {
			struct cache_entry *ce;

			ce = cache_file_exists(name->buf, name->len, ignore_case);
			if (ce && S_ISLNK(ce->ce_mode))
				return 1;
		} else {
