
	for_each_reflog_ent(refname, read_ref_at_ent_oldest, &cb);

	return 1;
}

struct ref_transaction *ref_transaction_begin(struct strbuf *err)
{
	assert(err);

	return xcalloc(1, sizeof(struct ref_transaction));
}
