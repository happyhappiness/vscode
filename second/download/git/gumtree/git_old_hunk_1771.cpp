		have_old = 1;
	}

	if (*next != line_termination)
		die("delete %s: extra input: %s", refname, next);

	ref_transaction_delete(transaction, refname, old_sha1,
			       update_flags, have_old);

	update_flags = 0;
	free(refname);

	return next;
}

static const char *parse_cmd_verify(struct strbuf *input, const char *next)
{
	char *refname;
	unsigned char new_sha1[20];
	unsigned char old_sha1[20];
	int have_old;

	refname = parse_refname(input, &next);
