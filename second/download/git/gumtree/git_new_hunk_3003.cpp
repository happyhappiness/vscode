		return error("Could not read index");

	fd = setup_rerere(&merge_rr, RERERE_NOAUTOUPDATE);
	if (fd < 0)
		return 0;

	/*
	 * The paths may have been resolved (incorrectly);
	 * recover the original conflicted state and then
	 * find the conflicted paths.
	 */
	unmerge_cache(pathspec);
	find_conflict(&conflict);
	for (i = 0; i < conflict.nr; i++) {
		struct string_list_item *it = &conflict.items[i];
		if (!match_pathspec(pathspec, it->string,
				    strlen(it->string), 0, NULL, 0))
			continue;
		rerere_forget_one_path(it->string, &merge_rr);
	}
	return write_rr(&merge_rr, fd);
}

/*
 * Garbage collection support
 */

/*
 * Note that this is not reentrant but is used only one-at-a-time
 * so it does not matter right now.
 */
static struct rerere_id *dirname_to_id(const char *name)
{
	static struct rerere_id id;
	strcpy(id.hex, name);
	return &id;
}

static time_t rerere_created_at(const char *dir_name)
{
	struct stat st;
	struct rerere_id *id = dirname_to_id(dir_name);

	return stat(rerere_path(id, "preimage"), &st) ? (time_t) 0 : st.st_mtime;
}

static time_t rerere_last_used_at(const char *dir_name)
{
	struct stat st;
	struct rerere_id *id = dirname_to_id(dir_name);

	return stat(rerere_path(id, "postimage"), &st) ? (time_t) 0 : st.st_mtime;
}

/*
 * Remove the recorded resolution for a given conflict ID
 */
static void unlink_rr_item(struct rerere_id *id)
{
	unlink(rerere_path(id, "thisimage"));
	unlink(rerere_path(id, "preimage"));
	unlink(rerere_path(id, "postimage"));
	/*
	 * NEEDSWORK: what if this rmdir() fails?  Wouldn't we then
	 * assume that we already have preimage recorded in
	 * do_plain_rerere()?
	 */
	rmdir(rerere_path(id, NULL));
}

void rerere_gc(struct string_list *rr)
{
	struct string_list to_remove = STRING_LIST_INIT_DUP;
	DIR *dir;
