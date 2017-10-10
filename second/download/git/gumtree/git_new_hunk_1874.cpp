	}
}

/* make sure nobody touched the ref, and unlink */
static void prune_ref(struct ref_to_prune *r)
{
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;

	if (check_refname_format(r->name, 0))
		return;

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_delete(transaction, r->name, r->sha1,
				   REF_ISPRUNING, 1, NULL, &err) ||
	    ref_transaction_commit(transaction, &err)) {
		ref_transaction_free(transaction);
		error("%s", err.buf);
		strbuf_release(&err);
		return;
	}
	ref_transaction_free(transaction);
	strbuf_release(&err);
	try_remove_empty_parents(r->name);
}

static void prune_refs(struct ref_to_prune *r)
{
	while (r) {
		prune_ref(r);
