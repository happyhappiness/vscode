	free_commit_list(common);
	parents = remoteheads;
	if (!head_subsumed || fast_forward == FF_NO)
		commit_list_insert(head, &parents);
	strbuf_addch(&merge_msg, '\n');
	prepare_to_commit(remoteheads);
	if (commit_tree(merge_msg.buf, merge_msg.len, result_tree, parents,
			result_commit, NULL, sign_commit))
		die(_("failed to write commit object"));
	strbuf_addf(&buf, "Merge made by the '%s' strategy.", wt_strategy);
	finish(head, remoteheads, result_commit, buf.buf);
	strbuf_release(&buf);
	drop_save();
	return 0;
