
static int files_transaction_commit(struct ref_store *ref_store,
				    struct ref_transaction *transaction,
				    struct strbuf *err)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, 0, "ref_transaction_commit");
	int ret = 0, i;
	struct string_list refs_to_delete = STRING_LIST_INIT_NODUP;
	struct string_list_item *ref_to_delete;
	struct string_list affected_refnames = STRING_LIST_INIT_NODUP;
	char *head_ref = NULL;
	int head_type;
	struct object_id head_oid;

	assert(err);

	if (transaction->state != REF_TRANSACTION_OPEN)
		die("BUG: commit called for transaction that is not open");

