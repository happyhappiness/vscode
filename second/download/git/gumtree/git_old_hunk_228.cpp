	struct ref **to_fetch = NULL;
	struct ref *list_head = NULL;
	struct ref **list = &list_head;
	int alloc_heads = 0, nr_heads = 0;

	do {
		if (starts_with(buf->buf, "fetch ")) {
			char *p = buf->buf + strlen("fetch ");
			char *name;
			struct ref *ref;
			unsigned char old_sha1[20];

			if (strlen(p) < 40 || get_sha1_hex(p, old_sha1))
				die("protocol error: expected sha/ref, got %s'", p);
			if (p[40] == ' ')
