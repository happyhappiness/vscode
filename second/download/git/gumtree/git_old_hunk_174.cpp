		tree_content_replace(&b->branch_tree, sha1, mode, NULL);
		return;
	}
	tree_content_set(&b->branch_tree, p, sha1, mode, NULL);
}

static void file_change_d(struct branch *b)
{
	const char *p = command_buf.buf + 2;
	static struct strbuf uq = STRBUF_INIT;
	const char *endp;

	strbuf_reset(&uq);
	if (!unquote_c_style(&uq, p, &endp)) {
		if (*endp)
			die("Garbage after path in: %s", command_buf.buf);
		p = uq.buf;
	}
	tree_content_remove(&b->branch_tree, p, NULL, 1);
}

static void file_change_cr(struct branch *b, int rename)
{
	const char *s, *d;
	static struct strbuf s_uq = STRBUF_INIT;
	static struct strbuf d_uq = STRBUF_INIT;
	const char *endp;
	struct tree_entry leaf;

	s = command_buf.buf + 2;
	strbuf_reset(&s_uq);
	if (!unquote_c_style(&s_uq, s, &endp)) {
		if (*endp != ' ')
			die("Missing space after source: %s", command_buf.buf);
	} else {
		endp = strchr(s, ' ');
