int peel_ref(const char *refname, unsigned char *sha1)
{
	struct ref_store *refs = get_ref_store(NULL);

	return refs->be->peel_ref(refs, refname, sha1);
}