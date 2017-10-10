	strbuf_release(&msg);
}

static int merge_trivial(struct commit *head, struct commit_list *remoteheads)
{
	unsigned char result_tree[20], result_commit[20];
	struct commit_list *parent = xmalloc(sizeof(*parent));

	write_tree_trivial(result_tree);
	printf(_("Wonderful.\n"));
	parent->item = head;
	parent->next = xmalloc(sizeof(*parent->next));
	parent->next->item = remoteheads->item;
	parent->next->next = NULL;
	prepare_to_commit(remoteheads);
	if (commit_tree(merge_msg.buf, merge_msg.len, result_tree, parent,
			result_commit, NULL, sign_commit))
		die(_("failed to write commit object"));
	finish(head, remoteheads, result_commit, "In-index merge");
	drop_save();
	return 0;
}
