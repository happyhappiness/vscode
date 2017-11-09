static int append_similar_ref(const char *refname, const struct object_id *oid,
			      int flags, void *cb_data)
{
	struct similar_ref_cb *cb = (struct similar_ref_cb *)(cb_data);
	char *branch = strrchr(refname, '/') + 1;
	const char *remote;

	/* A remote branch of the same name is deemed similar */
	if (skip_prefix(refname, "refs/remotes/", &remote) &&
	    !strcmp(branch, cb->base_ref))
		string_list_append(cb->similar_refs, remote);
	return 0;
}