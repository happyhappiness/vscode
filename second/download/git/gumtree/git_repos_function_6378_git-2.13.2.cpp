void base_ref_iterator_init(struct ref_iterator *iter,
			    struct ref_iterator_vtable *vtable)
{
	iter->vtable = vtable;
	iter->refname = NULL;
	iter->oid = NULL;
	iter->flags = 0;
}