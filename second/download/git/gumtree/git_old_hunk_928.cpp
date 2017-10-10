	strbuf_addbuf(&merge_msg, &msg);
	strbuf_release(&msg);
}

static int merge_trivial(struct commit *head, struct commit_list *remoteheads)
{
	unsigned char result_tree[20], result_commit[20];
	struct commit_list *parents, **pptr = &parents;
	static struct lock_file lock;

	hold_locked_index(&lock, LOCK_DIE_ON_ERROR);
	refresh_cache(REFRESH_QUIET);
	if (active_cache_changed &&
	    write_locked_index(&the_index, &lock, COMMIT_LOCK))
		return error(_("Unable to write index."));
	rollback_lock_file(&lock);

	write_tree_trivial(result_tree);
	printf(_("Wonderful.\n"));
	pptr = commit_list_append(head, pptr);
	pptr = commit_list_append(remoteheads->item, pptr);
	prepare_to_commit(remoteheads);
	if (commit_tree(merge_msg.buf, merge_msg.len, result_tree, parents,
			result_commit, NULL, sign_commit))
		die(_("failed to write commit object"));
	finish(head, remoteheads, result_commit, "In-index merge");
	drop_save();
	return 0;
}

static int finish_automerge(struct commit *head,
			    int head_subsumed,
			    struct commit_list *common,
			    struct commit_list *remoteheads,
			    unsigned char *result_tree,
			    const char *wt_strategy)
{
	struct commit_list *parents = NULL;
	struct strbuf buf = STRBUF_INIT;
	unsigned char result_commit[20];

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
}

static int suggest_conflicts(void)
