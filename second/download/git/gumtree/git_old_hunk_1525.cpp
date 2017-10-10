			return TRANSACTION_GENERIC_ERROR;
		}
	}
	return 0;
}

static int files_transaction_commit(struct ref_store *ref_store,
				    struct ref_transaction *transaction,
				    struct strbuf *err)
{
	struct files_ref_store *refs =
		files_downcast(ref_store, REF_STORE_WRITE,
			       "ref_transaction_commit");
	int ret = 0, i;
	struct string_list refs_to_delete = STRING_LIST_INIT_NODUP;
	struct string_list_item *ref_to_delete;
	struct string_list affected_refnames = STRING_LIST_INIT_NODUP;
	char *head_ref = NULL;
	int head_type;
	struct object_id head_oid;
	struct strbuf sb = STRBUF_INIT;

	assert(err);

	if (transaction->state != REF_TRANSACTION_OPEN)
		die("BUG: commit called for transaction that is not open");

	if (!transaction->nr) {
		transaction->state = REF_TRANSACTION_CLOSED;
		return 0;
	}

	/*
	 * Fail if a refname appears more than once in the
	 * transaction. (If we end up splitting up any updates using
	 * split_symref_update() or split_head_update(), those
	 * functions will check that the new updates don't have the
