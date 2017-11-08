const struct worktree *find_shared_symref(const char *symref,
					  const char *target)
{
	const struct worktree *existing = NULL;
	struct strbuf path = STRBUF_INIT;
	struct strbuf sb = STRBUF_INIT;
	static struct worktree **worktrees;
	int i = 0;

	if (worktrees)
		free_worktrees(worktrees);
	worktrees = get_worktrees(0);

	for (i = 0; worktrees[i]; i++) {
		struct worktree *wt = worktrees[i];
		if (wt->is_bare)
			continue;

		if (wt->is_detached && !strcmp(symref, "HEAD")) {
			if (is_worktree_being_rebased(wt, target)) {
				existing = wt;
				break;
			}
			if (is_worktree_being_bisected(wt, target)) {
				existing = wt;
				break;
			}
		}

		strbuf_reset(&path);
		strbuf_reset(&sb);
		strbuf_addf(&path, "%s/%s",
			    get_worktree_git_dir(wt),
			    symref);

		if (parse_ref(path.buf, &sb, NULL)) {
			continue;
		}

		if (!strcmp(sb.buf, target)) {
			existing = wt;
			break;
		}
	}

	strbuf_release(&path);
	strbuf_release(&sb);

	return existing;
}