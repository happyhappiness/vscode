static struct commit *get_commit_reference(const struct object_id *oid)
{
	struct commit *r = lookup_commit_reference(oid);
	if (!r)
		die(_("Not a valid commit name %s"), oid_to_hex(oid));
	return r;
}