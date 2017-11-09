static char *get_branch(const struct worktree *wt, const char *path)
{
	struct strbuf sb = STRBUF_INIT;
	struct object_id oid;
	const char *branch_name;

	if (strbuf_read_file(&sb, worktree_git_path(wt, "%s", path), 0) <= 0)
		goto got_nothing;

	while (sb.len && sb.buf[sb.len - 1] == '\n')
		strbuf_setlen(&sb, sb.len - 1);
	if (!sb.len)
		goto got_nothing;
	if (skip_prefix(sb.buf, "refs/heads/", &branch_name))
		strbuf_remove(&sb, 0, branch_name - sb.buf);
	else if (starts_with(sb.buf, "refs/"))
		;
	else if (!get_oid_hex(sb.buf, &oid)) {
		strbuf_reset(&sb);
		strbuf_add_unique_abbrev(&sb, oid.hash, DEFAULT_ABBREV);
	} else if (!strcmp(sb.buf, "detached HEAD")) /* rebase */
		goto got_nothing;
	else			/* bisect */
		;
	return strbuf_detach(&sb, NULL);

got_nothing:
	strbuf_release(&sb);
	return NULL;
}