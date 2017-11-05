static const char *parse_cmd_create(struct ref_transaction *transaction,
				    struct strbuf *input, const char *next)
{
	struct strbuf err = STRBUF_INIT;
	char *refname;
	unsigned char new_sha1[20];

	refname = parse_refname(input, &next);
	if (!refname)
		die("create: missing <ref>");

	if (parse_next_sha1(input, &next, new_sha1, "create", refname, 0))
		die("create %s: missing <newvalue>", refname);

	if (is_null_sha1(new_sha1))
		die("create %s: zero <newvalue>", refname);

	if (*next != line_termination)
		die("create %s: extra input: %s", refname, next);

	if (ref_transaction_create(transaction, refname, new_sha1,
				   update_flags, msg, &err))
		die("%s", err.buf);

	update_flags = 0;
	free(refname);
	strbuf_release(&err);

	return next;
}