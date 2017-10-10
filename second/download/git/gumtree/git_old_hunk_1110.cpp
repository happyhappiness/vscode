	return xstrfmt("%.*s%.*s", (int)prefix_len, url,
		       (int)anon_len, anon_part);
literal_copy:
	return xstrdup(url);
}

struct alternate_refs_data {
	alternate_ref_fn *fn;
	void *data;
};

static int refs_from_alternate_cb(struct alternate_object_database *e,
				  void *data)
{
	char *other;
	size_t len;
	struct remote *remote;
	struct transport *transport;
	const struct ref *extra;
	struct alternate_refs_data *cb = data;

	other = real_pathdup(e->path, 1);
	len = strlen(other);

	while (other[len-1] == '/')
		other[--len] = '\0';
	if (len < 8 || memcmp(other + len - 8, "/objects", 8))
		goto out;
	/* Is this a git repository with refs? */
	memcpy(other + len - 8, "/refs", 6);
	if (!is_directory(other))
		goto out;
	other[len - 8] = '\0';
	remote = remote_get(other);
	transport = transport_get(remote, other);
	for (extra = transport_get_remote_refs(transport);
	     extra;
	     extra = extra->next)
		cb->fn(extra, cb->data);
	transport_disconnect(transport);
out:
	free(other);
	return 0;
}

void for_each_alternate_ref(alternate_ref_fn fn, void *data)
{
	struct alternate_refs_data cb;
