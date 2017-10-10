		unlink(filename);
	}

	return 0;
}

int refs_delete_ref(struct ref_store *refs, const char *msg,
		    const char *refname,
		    const unsigned char *old_sha1,
		    unsigned int flags)
{
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;

	if (ref_type(refname) == REF_TYPE_PSEUDOREF) {
		assert(refs == get_main_ref_store());
		return delete_pseudoref(refname, old_sha1);
	}

	transaction = ref_store_transaction_begin(refs, &err);
	if (!transaction ||
	    ref_transaction_delete(transaction, refname, old_sha1,
				   flags, msg, &err) ||
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

int delete_ref(const char *msg, const char *refname,
	       const unsigned char *old_sha1, unsigned int flags)
{
	return refs_delete_ref(get_main_ref_store(), msg, refname,
			       old_sha1, flags);
}

int copy_reflog_msg(char *buf, const char *msg)
{
	char *cp = buf;
	char c;
	int wasspace = 1;

