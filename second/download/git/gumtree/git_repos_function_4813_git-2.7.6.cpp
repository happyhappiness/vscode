static void do_commit(const struct am_state *state)
{
	unsigned char tree[GIT_SHA1_RAWSZ], parent[GIT_SHA1_RAWSZ],
		      commit[GIT_SHA1_RAWSZ];
	unsigned char *ptr;
	struct commit_list *parents = NULL;
	const char *reflog_msg, *author;
	struct strbuf sb = STRBUF_INIT;

	if (run_hook_le(NULL, "pre-applypatch", NULL))
		exit(1);

	if (write_cache_as_tree(tree, 0, NULL))
		die(_("git write-tree failed to write a tree"));

	if (!get_sha1_commit("HEAD", parent)) {
		ptr = parent;
		commit_list_insert(lookup_commit(parent), &parents);
	} else {
		ptr = NULL;
		say(state, stderr, _("applying to an empty history"));
	}

	author = fmt_ident(state->author_name, state->author_email,
			state->ignore_date ? NULL : state->author_date,
			IDENT_STRICT);

	if (state->committer_date_is_author_date)
		setenv("GIT_COMMITTER_DATE",
			state->ignore_date ? "" : state->author_date, 1);

	if (commit_tree(state->msg, state->msg_len, tree, parents, commit,
				author, state->sign_commit))
		die(_("failed to write commit object"));

	reflog_msg = getenv("GIT_REFLOG_ACTION");
	if (!reflog_msg)
		reflog_msg = "am";

	strbuf_addf(&sb, "%s: %.*s", reflog_msg, linelen(state->msg),
			state->msg);

	update_ref(sb.buf, "HEAD", commit, ptr, 0, UPDATE_REFS_DIE_ON_ERR);

	if (state->rebasing) {
		FILE *fp = xfopen(am_path(state, "rewritten"), "a");

		assert(!is_null_sha1(state->orig_commit));
		fprintf(fp, "%s ", sha1_to_hex(state->orig_commit));
		fprintf(fp, "%s\n", sha1_to_hex(commit));
		fclose(fp);
	}

	run_hook_le(NULL, "post-applypatch", NULL);

	strbuf_release(&sb);
}