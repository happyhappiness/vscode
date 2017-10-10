	}
}

int walker_fetch(struct walker *walker, int targets, char **target,
		 const char **write_ref, const char *write_ref_log_details)
{
	struct strbuf refname = STRBUF_INIT;
	struct strbuf err = STRBUF_INIT;
	struct ref_transaction *transaction = NULL;
	unsigned char *sha1 = xmalloc(targets * 20);
	char *msg = NULL;
	int i, ret = -1;

	save_commit_buffer = 0;

	if (write_ref) {
		transaction = ref_transaction_begin(&err);
		if (!transaction) {
			error("%s", err.buf);
			goto done;
		}
	}

	if (!walker->get_recover) {
		for_each_ref(mark_complete, NULL);
		commit_list_sort_by_date(&complete);
	}

	for (i = 0; i < targets; i++) {
		if (interpret_target(walker, target[i], &sha1[20 * i])) {
			error("Could not interpret response from server '%s' as something to pull", target[i]);
			goto done;
		}
		if (process(walker, lookup_unknown_object(&sha1[20 * i])))
			goto done;
	}

	if (loop(walker))
		goto done;
	if (!write_ref) {
		ret = 0;
		goto done;
	}
	if (write_ref_log_details) {
		msg = xstrfmt("fetch from %s", write_ref_log_details);
	} else {
		msg = NULL;
	}
	for (i = 0; i < targets; i++) {
		if (!write_ref[i])
			continue;
		strbuf_reset(&refname);
		strbuf_addf(&refname, "refs/%s", write_ref[i]);
		if (ref_transaction_update(transaction, refname.buf,
					   &sha1[20 * i], NULL, 0, 0,
					   msg ? msg : "fetch (unknown)",
					   &err)) {
			error("%s", err.buf);
			goto done;
		}
	}
	if (ref_transaction_commit(transaction, &err)) {
		error("%s", err.buf);
		goto done;
	}

	ret = 0;

done:
	ref_transaction_free(transaction);
	free(msg);
	free(sha1);
	strbuf_release(&err);
	strbuf_release(&refname);
	return ret;
}

void walker_free(struct walker *walker)
{
	walker->cleanup(walker);
	free(walker);
