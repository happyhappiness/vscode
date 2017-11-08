static int collect_reflog(const char *ref, const unsigned char *sha1, int unused, void *cb_data)
{
	struct collected_reflog *e;
	struct collect_reflog_cb *cb = cb_data;
	size_t namelen = strlen(ref);

	e = xmalloc(sizeof(*e) + namelen + 1);
	hashcpy(e->sha1, sha1);
	memcpy(e->reflog, ref, namelen + 1);
	ALLOC_GROW(cb->e, cb->nr + 1, cb->alloc);
	cb->e[cb->nr++] = e;
	return 0;
}