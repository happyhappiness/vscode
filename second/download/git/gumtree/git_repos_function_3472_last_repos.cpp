int refs_peel_ref(struct ref_store *refs, const char *refname,
		  unsigned char *sha1)
{
	return refs->be->peel_ref(refs, refname, sha1);
}