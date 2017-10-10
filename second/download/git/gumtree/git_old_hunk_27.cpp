	printf(_("Wonderful.\n"));
	parent->item = head;
	parent->next = xmalloc(sizeof(*parent->next));
	parent->next->item = remoteheads->item;
	parent->next->next = NULL;
	prepare_to_commit(remoteheads);
	if (commit_tree(&merge_msg, result_tree, parent, result_commit, NULL,
			sign_commit))
		die(_("failed to write commit object"));
	finish(head, remoteheads, result_commit, "In-index merge");
	drop_save();
	return 0;
}

