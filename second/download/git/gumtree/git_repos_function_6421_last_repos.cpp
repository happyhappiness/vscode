static void try_remove_empty_parents(struct files_ref_store *refs,
				     const char *refname,
				     unsigned int flags)
{
	struct strbuf buf = STRBUF_INIT;
	struct strbuf sb = STRBUF_INIT;
	char *p, *q;
	int i;

	strbuf_addstr(&buf, refname);
	p = buf.buf;
	for (i = 0; i < 2; i++) { /* refs/{heads,tags,...}/ */
		while (*p && *p != '/')
			p++;
		/* tolerate duplicate slashes; see check_refname_format() */
		while (*p == '/')
			p++;
	}
	q = buf.buf + buf.len;
	while (flags & (REMOVE_EMPTY_PARENTS_REF | REMOVE_EMPTY_PARENTS_REFLOG)) {
		while (q > p && *q != '/')
			q--;
		while (q > p && *(q-1) == '/')
			q--;
		if (q == p)
			break;
		strbuf_setlen(&buf, q - buf.buf);

		strbuf_reset(&sb);
		files_ref_path(refs, &sb, buf.buf);
		if ((flags & REMOVE_EMPTY_PARENTS_REF) && rmdir(sb.buf))
			flags &= ~REMOVE_EMPTY_PARENTS_REF;

		strbuf_reset(&sb);
		files_reflog_path(refs, &sb, buf.buf);
		if ((flags & REMOVE_EMPTY_PARENTS_REFLOG) && rmdir(sb.buf))
			flags &= ~REMOVE_EMPTY_PARENTS_REFLOG;
	}
	strbuf_release(&buf);
	strbuf_release(&sb);
}