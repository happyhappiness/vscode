		opt.cleanup_mode = CLEANUP_NONE;
	else if (!strcmp(cleanup_arg, "whitespace"))
		opt.cleanup_mode = CLEANUP_SPACE;
	else
		die(_("Invalid cleanup mode %s"), cleanup_arg);

	create_reflog_msg(&object, &reflog_msg);

	if (create_tag_object) {
		if (force_sign_annotate && !annotate)
			opt.sign = 1;
		create_tag(&object, tag, &buf, &opt, &prev, &object);
	}

	transaction = ref_transaction_begin(&err);
	if (!transaction ||
	    ref_transaction_update(transaction, ref.buf, object.hash, prev.hash,
				   create_reflog ? REF_FORCE_CREATE_REFLOG : 0,
				   reflog_msg.buf, &err) ||
	    ref_transaction_commit(transaction, &err))
		die("%s", err.buf);
	ref_transaction_free(transaction);
	if (force && !is_null_oid(&prev) && oidcmp(&prev, &object))
		printf(_("Updated tag '%s' (was %s)\n"), tag, find_unique_abbrev(prev.hash, DEFAULT_ABBREV));

	strbuf_release(&err);
	strbuf_release(&buf);
	strbuf_release(&ref);
	strbuf_release(&reflog_msg);
	return 0;
