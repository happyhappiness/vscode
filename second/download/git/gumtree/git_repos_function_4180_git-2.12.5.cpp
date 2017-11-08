static int ignore_symref_update(const char *refname)
{
	struct object_id oid;
	int flag;

	if (!resolve_ref_unsafe(refname, 0, oid.hash, &flag))
		return 0; /* non-existing refs are OK */
	return (flag & REF_ISSYMREF);
}