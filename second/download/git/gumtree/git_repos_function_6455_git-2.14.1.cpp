void base_ref_iterator_free(struct ref_iterator *iter)
{
	/* Help make use-after-free bugs fail quickly: */
	iter->vtable = NULL;
	free(iter);
}