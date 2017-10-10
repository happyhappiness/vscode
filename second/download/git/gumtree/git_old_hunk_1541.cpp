}

static void prepare_show_merge(struct rev_info *revs)
{
	struct commit_list *bases;
	struct commit *head, *other;
	unsigned char sha1[20];
	const char **prune = NULL;
	int i, prune_num = 1; /* counting terminating NULL */

	if (get_sha1("HEAD", sha1))
		die("--merge without HEAD?");
	head = lookup_commit_or_die(sha1, "HEAD");
	if (get_sha1("MERGE_HEAD", sha1))
		die("--merge without MERGE_HEAD?");
	other = lookup_commit_or_die(sha1, "MERGE_HEAD");
	add_pending_object(revs, &head->object, "HEAD");
	add_pending_object(revs, &other->object, "MERGE_HEAD");
	bases = get_merge_bases(head, other);
	add_rev_cmdline_list(revs, bases, REV_CMD_MERGE_BASE, UNINTERESTING | BOTTOM);
	add_pending_commit_list(revs, bases, UNINTERESTING | BOTTOM);
	free_commit_list(bases);
