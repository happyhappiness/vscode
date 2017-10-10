		}
	}
	return 0;

found_entry:
	memcpy(leaf, e, sizeof(*leaf));
	if (e->tree && is_null_oid(&e->versions[1].oid))
		leaf->tree = dup_tree_content(e->tree);
	else
		leaf->tree = NULL;
	return 1;
}

static int update_branch(struct branch *b)
{
	static const char *msg = "fast-import";
	struct ref_transaction *transaction;
	struct object_id old_oid;
	struct strbuf err = STRBUF_INIT;

	if (is_null_oid(&b->oid)) {
		if (b->delete)
			delete_ref(NULL, b->name, NULL, 0);
		return 0;
	}
	if (read_ref(b->name, old_oid.hash))
		oidclr(&old_oid);
	if (!force_update && !is_null_oid(&old_oid)) {
		struct commit *old_cmit, *new_cmit;

		old_cmit = lookup_commit_reference_gently(&old_oid, 0);
		new_cmit = lookup_commit_reference_gently(&b->oid, 0);
		if (!old_cmit || !new_cmit)
			return error("Branch %s is missing commits.", b->name);

		if (!in_merge_bases(old_cmit, new_cmit)) {
			warning("Not updating %s"
				" (new tip %s does not contain %s)",
				b->name, oid_to_hex(&b->oid),
				oid_to_hex(&old_oid));
			return -1;
		}
	}
	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_update(transaction, b->name, b->oid.hash, old_oid.hash,
				   0, msg, &err) ||
	    ref_transaction_commit(transaction, &err)) {
		ref_transaction_free(transaction);
		error("%s", err.buf);
		strbuf_release(&err);
		return -1;
