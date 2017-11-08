int refs_init_db(struct strbuf *err)
{
	struct ref_store *refs = get_ref_store(NULL);

	return refs->be->init_db(refs, err);
}