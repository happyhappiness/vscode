static const char *parse_cmd_delete(struct ref_transaction *transaction,
				    struct strbuf *input, const char *next)
{
	struct strbuf err = STRBUF_INIT;
	char *refname;
	unsigned char old_sha1[20];
	int have_old;

	refname = parse_refname(input, &next);
	if (!refname)
		die("delete: missing <ref>");

	if (parse_next_sha1(input, &next, old_sha1, "delete", refname,
			    PARSE_SHA1_OLD)) {
		have_old = 0;
	} else {
		if (is_null_sha1(old_sha1))
			die("delete %s: zero <oldvalue>", refname);
		have_old = 1;
	}

	if (*next != line_termination)
		die("delete %s: extra input: %s", refname, next);

	if (ref_transaction_delete(transaction, refname, old_sha1,
				   update_flags, have_old, msg, &err))
		die("%s", err.buf);

	update_flags = 0;
	free(refname);
	strbuf_release(&err);

	return next;
}