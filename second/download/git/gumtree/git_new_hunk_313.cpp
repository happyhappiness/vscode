 * Commits the current index with state->msg as the commit message and
 * state->author_name, state->author_email and state->author_date as the author
 * information.
 */
static void do_commit(const struct am_state *state)
{
	struct object_id tree, parent, commit;
	const struct object_id *old_oid;
	struct commit_list *parents = NULL;
	const char *reflog_msg, *author;
	struct strbuf sb = STRBUF_INIT;

	if (run_hook_le(NULL, "pre-applypatch", NULL))
		exit(1);

	if (write_cache_as_tree(tree.hash, 0, NULL))
		die(_("git write-tree failed to write a tree"));

	if (!get_sha1_commit("HEAD", parent.hash)) {
		old_oid = &parent;
		commit_list_insert(lookup_commit(parent.hash), &parents);
	} else {
		old_oid = NULL;
		say(state, stderr, _("applying to an empty history"));
	}

	author = fmt_ident(state->author_name, state->author_email,
			state->ignore_date ? NULL : state->author_date,
			IDENT_STRICT);

	if (state->committer_date_is_author_date)
		setenv("GIT_COMMITTER_DATE",
			state->ignore_date ? "" : state->author_date, 1);

	if (commit_tree(state->msg, state->msg_len, tree.hash, parents, commit.hash,
				author, state->sign_commit))
		die(_("failed to write commit object"));

	reflog_msg = getenv("GIT_REFLOG_ACTION");
	if (!reflog_msg)
		reflog_msg = "am";

	strbuf_addf(&sb, "%s: %.*s", reflog_msg, linelen(state->msg),
			state->msg);

	update_ref_oid(sb.buf, "HEAD", &commit, old_oid, 0,
			UPDATE_REFS_DIE_ON_ERR);

	if (state->rebasing) {
		FILE *fp = xfopen(am_path(state, "rewritten"), "a");

		assert(!is_null_oid(&state->orig_commit));
		fprintf(fp, "%s ", oid_to_hex(&state->orig_commit));
		fprintf(fp, "%s\n", oid_to_hex(&commit));
		fclose(fp);
	}

	run_hook_le(NULL, "post-applypatch", NULL);

	strbuf_release(&sb);
