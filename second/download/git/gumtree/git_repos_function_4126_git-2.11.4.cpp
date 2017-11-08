static void set_merge(struct branch *ret)
{
	struct remote *remote;
	char *ref;
	struct object_id oid;
	int i;

	if (!ret)
		return; /* no branch */
	if (ret->merge)
		return; /* already run */
	if (!ret->remote_name || !ret->merge_nr) {
		/*
		 * no merge config; let's make sure we don't confuse callers
		 * with a non-zero merge_nr but a NULL merge
		 */
		ret->merge_nr = 0;
		return;
	}

	remote = remote_get(ret->remote_name);

	ret->merge = xcalloc(ret->merge_nr, sizeof(*ret->merge));
	for (i = 0; i < ret->merge_nr; i++) {
		ret->merge[i] = xcalloc(1, sizeof(**ret->merge));
		ret->merge[i]->src = xstrdup(ret->merge_name[i]);
		if (!remote_find_tracking(remote, ret->merge[i]) ||
		    strcmp(ret->remote_name, "."))
			continue;
		if (dwim_ref(ret->merge_name[i], strlen(ret->merge_name[i]),
			     oid.hash, &ref) == 1)
			ret->merge[i]->dst = ref;
		else
			ret->merge[i]->dst = xstrdup(ret->merge_name[i]);
	}
}