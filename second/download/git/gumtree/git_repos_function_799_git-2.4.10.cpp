static char *read_and_strip_branch(const char *path)
{
	struct strbuf sb = STRBUF_INIT;
	unsigned char sha1[20];

	if (strbuf_read_file(&sb, git_path("%s", path), 0) <= 0)
		goto got_nothing;

	while (sb.len && sb.buf[sb.len - 1] == '\n')
		strbuf_setlen(&sb, sb.len - 1);
	if (!sb.len)
		goto got_nothing;
	if (starts_with(sb.buf, "refs/heads/"))
		strbuf_remove(&sb,0, strlen("refs/heads/"));
	else if (starts_with(sb.buf, "refs/"))
		;
	else if (!get_sha1_hex(sb.buf, sha1)) {
		const char *abbrev;
		abbrev = find_unique_abbrev(sha1, DEFAULT_ABBREV);
		strbuf_reset(&sb);
		strbuf_addstr(&sb, abbrev);
	} else if (!strcmp(sb.buf, "detached HEAD")) /* rebase */
		goto got_nothing;
	else			/* bisect */
		;
	return strbuf_detach(&sb, NULL);

got_nothing:
	strbuf_release(&sb);
	return NULL;
}