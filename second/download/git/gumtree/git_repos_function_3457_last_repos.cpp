int refs_read_raw_ref(struct ref_store *ref_store,
		      const char *refname, unsigned char *sha1,
		      struct strbuf *referent, unsigned int *type)
{
	return ref_store->be->read_raw_ref(ref_store, refname, sha1, referent, type);
}