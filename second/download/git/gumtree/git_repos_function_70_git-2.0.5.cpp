static int append_similar_ref(const char *refname, const unsigned char *sha1,
			      int flags, void *cb_data)
{
	struct similar_ref_cb *cb = (struct similar_ref_cb *)(cb_data);
	char *branch = strrchr(refname, '/') + 1;
	/* A remote branch of the same name is deemed similar */
	if (starts_with(refname, "refs/remotes/") &&
	    !strcmp(branch, cb->base_ref))
		string_list_append(cb->similar_refs,
				   refname + strlen("refs/remotes/"));
	return 0;
}