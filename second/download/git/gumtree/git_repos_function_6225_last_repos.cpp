static int finish_automerge(struct commit *head,
			    int head_subsumed,
			    struct commit_list *common,
			    struct commit_list *remoteheads,
			    struct object_id *result_tree,
			    const char *wt_strategy)
{
	struct commit_list *parents = NULL;
	struct strbuf buf = STRBUF_INIT;
	struct object_id result_commit;

	free_commit_list(common);
	parents = remoteheads;
	if (!head_subsumed || fast_forward == FF_NO)
		commit_list_insert(head, &parents);
	strbuf_addch(&merge_msg, '\n');
	prepare_to_commit(remoteheads);
	if (commit_tree(merge_msg.buf, merge_msg.len, result_tree->hash, parents,
			result_commit.hash, NULL, sign_commit))
		die(_("failed to write commit object"));
	strbuf_addf(&buf, "Merge made by the '%s' strategy.", wt_strategy);
	finish(head, remoteheads, &result_commit, buf.buf);
	strbuf_release(&buf);
	drop_save();
	return 0;
}