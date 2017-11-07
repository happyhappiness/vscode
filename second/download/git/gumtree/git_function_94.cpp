static const char *parse_cmd_verify(struct strbuf *input, const char *next)
{
	char *refname;
	unsigned char new_sha1[20];
	unsigned char old_sha1[20];
	int have_old;

	refname = parse_refname(input, &next);
	if (!refname)
		die("verify: missing <ref>");

	if (parse_next_sha1(input, &next, old_sha1, "verify", refname,
			    PARSE_SHA1_OLD)) {
		hashclr(new_sha1);
		have_old = 0;
	} else {
		hashcpy(new_sha1, old_sha1);
		have_old = 1;
	}

	if (*next != line_termination)
		die("verify %s: extra input: %s", refname, next);

	if (ref_transaction_update(transaction, refname, new_sha1, old_sha1,
				   update_flags, have_old, &err))
		die("%s", err.buf);

	update_flags = 0;
	free(refname);

	return next;
}