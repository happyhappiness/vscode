		rollback_index_files();
		die(_("failed to write commit object"));
	}
	strbuf_release(&author_ident);
	free_commit_extra_headers(extra);

	nl = strchr(sb.buf, '\n');
	if (nl)
		strbuf_setlen(&sb, nl + 1 - sb.buf);
	else
		strbuf_addch(&sb, '\n');
	strbuf_insert(&sb, 0, reflog_msg, strlen(reflog_msg));
	strbuf_insert(&sb, strlen(reflog_msg), ": ", 2);

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_update(transaction, "HEAD", sha1,
				   current_head
				   ? current_head->object.sha1 : NULL,
				   0, !!current_head, sb.buf, &err) ||
	    ref_transaction_commit(transaction, &err)) {
		rollback_index_files();
		die("%s", err.buf);
	}
	ref_transaction_free(transaction);

	unlink(git_path("CHERRY_PICK_HEAD"));
	unlink(git_path("REVERT_HEAD"));
	unlink(git_path("MERGE_HEAD"));
	unlink(git_path("MERGE_MSG"));
	unlink(git_path("MERGE_MODE"));
	unlink(git_path("SQUASH_MSG"));

	if (commit_index_files())
		die (_("Repository has been updated, but unable to write\n"
		     "new_index file. Check that disk is not full and quota is\n"
		     "not exceeded, and then \"git reset HEAD\" to recover."));

	rerere(0);
	run_commit_hook(use_editor, get_index_file(), "post-commit", NULL);
	if (amend && !no_post_rewrite) {
		struct notes_rewrite_cfg *cfg;
