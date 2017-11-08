char *find_shared_symref(const char *symref, const char *target)
{
	char *existing = NULL;
	struct strbuf path = STRBUF_INIT;
	struct strbuf sb = STRBUF_INIT;
	struct worktree **worktrees = get_worktrees();
	int i = 0;

	for (i = 0; worktrees[i]; i++) {
		strbuf_reset(&path);
		strbuf_reset(&sb);
		strbuf_addf(&path, "%s/%s", worktrees[i]->git_dir, symref);

		if (parse_ref(path.buf, &sb, NULL)) {
			continue;
		}

		if (!strcmp(sb.buf, target)) {
			existing = xstrdup(worktrees[i]->path);
			break;
		}
	}

	strbuf_release(&path);
	strbuf_release(&sb);
	free_worktrees(worktrees);

	return existing;
}