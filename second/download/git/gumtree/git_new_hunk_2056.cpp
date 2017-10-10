
static const char *parse_cmd_verify(struct ref_transaction *transaction,
				    struct strbuf *input, const char *next)
{
	struct strbuf err = STRBUF_INIT;
	char *refname;
	unsigned char old_sha1[20];

	refname = parse_refname(input, &next);
	if (!refname)
		die("verify: missing <ref>");

	if (parse_next_sha1(input, &next, old_sha1, "verify", refname,
			    PARSE_SHA1_OLD))
		hashclr(old_sha1);

	if (*next != line_termination)
		die("verify %s: extra input: %s", refname, next);

	if (ref_transaction_verify(transaction, refname, old_sha1,
				   update_flags, &err))
		die("%s", err.buf);

	update_flags = 0;
	free(refname);
	strbuf_release(&err);

