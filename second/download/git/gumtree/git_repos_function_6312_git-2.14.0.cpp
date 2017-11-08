static int replace_object_oid(const char *object_ref,
			       struct object_id *object,
			       const char *replace_ref,
			       struct object_id *repl,
			       int force)
{
	struct object_id prev;
	enum object_type obj_type, repl_type;
	struct strbuf ref = STRBUF_INIT;
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;

	obj_type = sha1_object_info(object->hash, NULL);
	repl_type = sha1_object_info(repl->hash, NULL);
	if (!force && obj_type != repl_type)
		die("Objects must be of the same type.\n"
		    "'%s' points to a replaced object of type '%s'\n"
		    "while '%s' points to a replacement object of type '%s'.",
		    object_ref, typename(obj_type),
		    replace_ref, typename(repl_type));

	check_ref_valid(object, &prev, &ref, force);

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_update(transaction, ref.buf, repl->hash, prev.hash,
				   0, NULL, &err) ||
	    ref_transaction_commit(transaction, &err))
		die("%s", err.buf);

	ref_transaction_free(transaction);
	strbuf_release(&ref);
	return 0;
}