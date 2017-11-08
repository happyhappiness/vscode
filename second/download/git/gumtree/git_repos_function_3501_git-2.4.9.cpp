static int ignore_symref_update(const char *refname)
{
	unsigned char sha1[20];
	int flag;

	if (!resolve_ref_unsafe(refname, 0, sha1, &flag))
		return 0; /* non-existing refs are OK */
	return (flag & REF_ISSYMREF);
}