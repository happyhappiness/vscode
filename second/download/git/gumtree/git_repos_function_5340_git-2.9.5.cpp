static void write_remote_refs(const struct ref *local_refs)
{
	const struct ref *r;

	struct ref_transaction *t;
	struct strbuf err = STRBUF_INIT;

	t = ref_transaction_begin(&err);
	if (!t)
		die("%s", err.buf);

	for (r = local_refs; r; r = r->next) {
		if (!r->peer_ref)
			continue;
		if (ref_transaction_create(t, r->peer_ref->name, r->old_oid.hash,
					   0, NULL, &err))
			die("%s", err.buf);
	}

	if (initial_ref_transaction_commit(t, &err))
		die("%s", err.buf);

	strbuf_release(&err);
	ref_transaction_free(t);
}