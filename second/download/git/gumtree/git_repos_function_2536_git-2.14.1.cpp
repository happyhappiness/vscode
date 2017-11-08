static struct combine_diff_path *path_appendnew(struct combine_diff_path *last,
	int nparent, const struct strbuf *base, const char *path, int pathlen,
	unsigned mode, const struct object_id *oid)
{
	struct combine_diff_path *p;
	size_t len = st_add(base->len, pathlen);
	size_t alloclen = combine_diff_path_size(nparent, len);

	/* if last->next is !NULL - it is a pre-allocated memory, we can reuse */
	p = last->next;
	if (p && (alloclen > (intptr_t)p->next)) {
		FREE_AND_NULL(p);
	}

	if (!p) {
		p = xmalloc(alloclen);

		/*
		 * until we go to it next round, .next holds how many bytes we
		 * allocated (for faster realloc - we don't need copying old data).
		 */
		p->next = (struct combine_diff_path *)(intptr_t)alloclen;
	}

	last->next = p;

	p->path = (char *)&(p->parent[nparent]);
	memcpy(p->path, base->buf, base->len);
	memcpy(p->path + base->len, path, pathlen);
	p->path[len] = 0;
	p->mode = mode;
	oidcpy(&p->oid, oid ? oid : &null_oid);

	return p;
}