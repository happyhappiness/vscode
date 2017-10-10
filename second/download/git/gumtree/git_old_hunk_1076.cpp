		unlink(filename);
	}

	return 0;
}

int delete_ref(const char *refname, const unsigned char *old_sha1,
	       unsigned int flags)
{
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;

	if (ref_type(refname) == REF_TYPE_PSEUDOREF)
		return delete_pseudoref(refname, old_sha1);

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_delete(transaction, refname, old_sha1,
				   flags, NULL, &err) ||
	    ref_transaction_commit(transaction, &err)) {
		error("%s", err.buf);
		ref_transaction_free(transaction);
		strbuf_release(&err);
		return 1;
	}
	ref_transaction_free(transaction);
	strbuf_release(&err);
	return 0;
}

int copy_reflog_msg(char *buf, const char *msg)
{
	char *cp = buf;
	char c;
	int wasspace = 1;

