static int verify_merge_base(struct object_id *head_oid, struct ref *remote)
{
	struct commit *head = lookup_commit_or_die(head_oid, "HEAD");
	struct commit *branch = lookup_commit_or_die(&remote->old_oid,
						     remote->name);

	return in_merge_bases(branch, head);
}