	strbuf_release(&msg);
}

static int merge_trivial(struct commit *head, struct commit_list *remoteheads)
{
	unsigned char result_tree[20], result_commit[20];
	struct commit_list *parents, **pptr = &parents;

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
