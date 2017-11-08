struct ref *copy_ref(const struct ref *ref)
{
	struct ref *cpy;
	size_t len;
	if (!ref)
		return NULL;
	len = strlen(ref->name);
	cpy = xmalloc(sizeof(struct ref) + len + 1);
	memcpy(cpy, ref, sizeof(struct ref) + len + 1);
	cpy->next = NULL;
	cpy->symref = ref->symref ? xstrdup(ref->symref) : NULL;
	cpy->remote_status = ref->remote_status ? xstrdup(ref->remote_status) : NULL;
	cpy->peer_ref = copy_ref(ref->peer_ref);
	return cpy;
}