		if (remove_entry(packed, ref_to_delete->string) == -1)
			die("internal error");
	}

	/* Write what remains */
	ret = commit_packed_refs();
	if (ret)
		strbuf_addf(err, "unable to overwrite old ref-pack file: %s",
			    strerror(errno));
	return ret;
}

static int delete_ref_loose(struct ref_lock *lock, int flag, struct strbuf *err)
{
	assert(err);

	if (!(flag & REF_ISPACKED) || flag & REF_ISSYMREF) {
		/*
		 * loose.  The loose file name is the same as the
		 * lockfile name, minus ".lock":
		 */
		char *loose_filename = get_locked_file_path(lock->lk);
		int res = unlink_or_msg(loose_filename, err);
		free(loose_filename);
		if (res)
			return 1;
	}
	return 0;
}

int delete_ref(const char *refname, const unsigned char *sha1, int delopt)
{
	struct ref_transaction *transaction;
	struct strbuf err = STRBUF_INIT;

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_delete(transaction, refname, sha1, delopt,
				   sha1 && !is_null_sha1(sha1), NULL, &err) ||
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

/*
 * People using contrib's git-new-workdir have .git/logs/refs ->
 * /some/other/path/.git/logs/refs, and that may live on another device.
 *
