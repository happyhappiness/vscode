{
	if (!branch || i < 0 || i >= branch->merge_nr)
		return 0;
	return refname_match(branch->merge[i]->src, refname);
}

static int ignore_symref_update(const char *refname)
{
	unsigned char sha1[20];
	int flag;

	if (!resolve_ref_unsafe(refname, 0, sha1, &flag))
