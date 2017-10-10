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

