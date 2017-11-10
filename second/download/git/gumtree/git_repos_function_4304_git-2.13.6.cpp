struct ref *copy_ref(const struct ref *ref)
{
	struct ref *cpy;
	size_t len;
	if (!ref)
		return NULL;
	len = st_add3(sizeof(struct ref), strlen(ref->name), 1);
	cpy = xmalloc(len);
	memcpy(cpy, ref, len);
	cpy->next = NULL;
	cpy->symref = xstrdup_or_null(ref->symref);
	cpy->remote_status = xstrdup_or_null(ref->remote_status);
	cpy->peer_ref = copy_ref(ref->peer_ref);
	return cpy;
}