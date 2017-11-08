static int check_has_commit(const struct object_id *oid, void *data)
{
	int *has_commit = data;

	if (!lookup_commit_reference(oid))
		*has_commit = 0;

	return 0;
}