 */
static int get_mail_commit_oid(struct object_id *commit_id, const char *mail)
{
	struct strbuf sb = STRBUF_INIT;
	FILE *fp = xfopen(mail, "r");
	const char *x;
	int ret = 0;

	if (strbuf_getline_lf(&sb, fp) ||
	    !skip_prefix(sb.buf, "From ", &x) ||
	    get_oid_hex(x, commit_id) < 0)
		ret = -1;

	strbuf_release(&sb);
	fclose(fp);
	return ret;
}

/**
 * Sets state->msg, state->author_name, state->author_email, state->author_date
 * to the commit's respective info.
 */
static void get_commit_info(struct am_state *state, struct commit *commit)
{
	const char *buffer, *ident_line, *msg;
	size_t ident_len;
	struct ident_split id;

	buffer = logmsg_reencode(commit, NULL, get_commit_output_encoding());

	ident_line = find_commit_header(buffer, "author", &ident_len);

	if (split_ident_line(&id, ident_line, ident_len) < 0)
		die(_("invalid ident line: %.*s"), (int)ident_len, ident_line);

	assert(!state->author_name);
	if (id.name_begin)
		state->author_name =
			xmemdupz(id.name_begin, id.name_end - id.name_begin);
	else
		state->author_name = xstrdup("");

	assert(!state->author_email);
	if (id.mail_begin)
		state->author_email =
			xmemdupz(id.mail_begin, id.mail_end - id.mail_begin);
	else
		state->author_email = xstrdup("");

	assert(!state->author_date);
	state->author_date = xstrdup(show_ident_date(&id, DATE_MODE(NORMAL)));

	assert(!state->msg);
	msg = strstr(buffer, "\n\n");
	if (!msg)
		die(_("unable to parse commit %s"), oid_to_hex(&commit->object.oid));
	state->msg = xstrdup(msg + 2);
	state->msg_len = strlen(state->msg);
	unuse_commit_buffer(commit, buffer);
}

/**
 * Writes `commit` as a patch to the state directory's "patch" file.
 */
static void write_commit_patch(const struct am_state *state, struct commit *commit)
