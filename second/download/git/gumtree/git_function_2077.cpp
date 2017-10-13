static void check_linked_checkout(struct branch_info *new, const char *id)
{
	struct strbuf sb = STRBUF_INIT;
	struct strbuf path = STRBUF_INIT;
	struct strbuf gitdir = STRBUF_INIT;
	const char *start, *end;

	if (id)
		strbuf_addf(&path, "%s/worktrees/%s/HEAD", get_git_common_dir(), id);
	else
		strbuf_addf(&path, "%s/HEAD", get_git_common_dir());

	if (strbuf_read_file(&sb, path.buf, 0) < 0 ||
	    !skip_prefix(sb.buf, "ref:", &start))
		goto done;
	while (isspace(*start))
		start++;
	end = start;
	while (*end && !isspace(*end))
		end++;
	if (strncmp(start, new->path, end - start) || new->path[end - start] != '\0')
		goto done;
	if (id) {
		strbuf_reset(&path);
		strbuf_addf(&path, "%s/worktrees/%s/gitdir", get_git_common_dir(), id);
		if (strbuf_read_file(&gitdir, path.buf, 0) <= 0)
			goto done;
		strbuf_rtrim(&gitdir);
	} else
		strbuf_addstr(&gitdir, get_git_common_dir());
	die(_("'%s' is already checked out at '%s'"), new->name, gitdir.buf);
done:
	strbuf_release(&path);
	strbuf_release(&sb);
	strbuf_release(&gitdir);
}