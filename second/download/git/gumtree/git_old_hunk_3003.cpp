		return error("Could not read index");

	fd = setup_rerere(&merge_rr, RERERE_NOAUTOUPDATE);
	if (fd < 0)
		return 0;

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

static time_t rerere_created_at(const char *name)
{
	struct stat st;
	return stat(rerere_path(name, "preimage"), &st) ? (time_t) 0 : st.st_mtime;
}

static time_t rerere_last_used_at(const char *name)
{
	struct stat st;
	return stat(rerere_path(name, "postimage"), &st) ? (time_t) 0 : st.st_mtime;
}

static void unlink_rr_item(const char *name)
{
	unlink(rerere_path(name, "thisimage"));
	unlink(rerere_path(name, "preimage"));
	unlink(rerere_path(name, "postimage"));
	rmdir(git_path("rr-cache/%s", name));
}

void rerere_gc(struct string_list *rr)
{
	struct string_list to_remove = STRING_LIST_INIT_DUP;
	DIR *dir;
