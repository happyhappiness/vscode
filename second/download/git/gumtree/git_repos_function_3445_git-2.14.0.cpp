int refs_init_db(struct strbuf *err)
{
	struct ref_store *refs = get_main_ref_store();

	return refs->be->init_db(refs, err);
}