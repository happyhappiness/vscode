void base_ref_store_init(struct ref_store *refs,
			 const struct ref_storage_be *be)
{
	refs->be = be;
}