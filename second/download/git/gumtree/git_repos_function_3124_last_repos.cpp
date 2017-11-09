static void parse_fetch(struct strbuf *buf)
{
	struct ref **to_fetch = NULL;
	struct ref *list_head = NULL;
	struct ref **list = &list_head;
	int alloc_heads = 0, nr_heads = 0;

	do {
		const char *p;
		if (skip_prefix(buf->buf, "fetch ", &p)) {
			const char *name;
			struct ref *ref;
			struct object_id old_oid;

			if (get_oid_hex(p, &old_oid))
				die("protocol error: expected sha/ref, got %s'", p);
			if (p[GIT_SHA1_HEXSZ] == ' ')
				name = p + GIT_SHA1_HEXSZ + 1;
			else if (!p[GIT_SHA1_HEXSZ])
				name = "";
			else
				die("protocol error: expected sha/ref, got %s'", p);

			ref = alloc_ref(name);
			oidcpy(&ref->old_oid, &old_oid);

			*list = ref;
			list = &ref->next;

			ALLOC_GROW(to_fetch, nr_heads + 1, alloc_heads);
			to_fetch[nr_heads++] = ref;
		}
		else
			die("http transport does not support %s", buf->buf);

		strbuf_reset(buf);
		if (strbuf_getline_lf(buf, stdin) == EOF)
			return;
		if (!*buf->buf)
			break;
	} while (1);

	if (fetch(nr_heads, to_fetch))
		exit(128); /* error already reported */
	free_refs(list_head);
	free(to_fetch);

	printf("\n");
	fflush(stdout);
	strbuf_reset(buf);
}