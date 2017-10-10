			   NULL, REF_NODEREF, UPDATE_REFS_DIE_ON_ERR);
	}
}

static int checkout(int submodule_progress)
{
	unsigned char sha1[20];
	char *head;
	struct lock_file *lock_file;
	struct unpack_trees_options opts;
	struct tree *tree;
	struct tree_desc t;
	int err = 0;

	if (option_no_checkout)
		return 0;

	head = resolve_refdup("HEAD", RESOLVE_REF_READING, sha1, NULL);
	if (!head) {
		warning(_("remote HEAD refers to nonexistent ref, "
			  "unable to checkout.\n"));
		return 0;
	}
	if (!strcmp(head, "HEAD")) {
		if (advice_detached_head)
			detach_advice(sha1_to_hex(sha1));
	} else {
		if (!starts_with(head, "refs/heads/"))
			die(_("HEAD not found below refs/heads!"));
	}
	free(head);

