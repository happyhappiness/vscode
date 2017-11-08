struct commit *lookup_commit_reference(const struct object_id *oid)
{
	return lookup_commit_reference_gently(oid, 0);
}