				    PARSE_SHA1_OLD);

	if (*next != line_termination)
		die("update %s: extra input: %s", refname, next);

	if (ref_transaction_update(transaction, refname, new_sha1, old_sha1,
				   update_flags, have_old, &err))
		die("%s", err.buf);

	update_flags = 0;
	free(refname);

	return next;
}

static const char *parse_cmd_create(struct strbuf *input, const char *next)
{
	char *refname;
	unsigned char new_sha1[20];

	refname = parse_refname(input, &next);
	if (!refname)
		die("create: missing <ref>");
