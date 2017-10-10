	}

	if (*next != line_termination)
		die("verify %s: extra input: %s", refname, next);

	if (ref_transaction_update(transaction, refname, new_sha1, old_sha1,
				   update_flags, have_old, msg, &err))
		die("%s", err.buf);

	update_flags = 0;
	free(refname);
	strbuf_release(&err);

	return next;
}

static const char *parse_cmd_option(struct strbuf *input, const char *next)
{
