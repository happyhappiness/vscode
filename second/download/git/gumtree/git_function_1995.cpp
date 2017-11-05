static void add_remote_info_ref(struct remote_ls_ctx *ls)
{
	struct strbuf *buf = (struct strbuf *)ls->userData;
	struct object *o;
	int len;
	char *ref_info;
	struct ref *ref;

	ref = alloc_ref(ls->dentry_name);

	if (http_fetch_ref(repo->url, ref) != 0) {
		fprintf(stderr,
			"Unable to fetch ref %s from %s\n",
			ls->dentry_name, repo->url);
		aborted = 1;
		free(ref);
		return;
	}

	o = parse_object(ref->old_sha1);
	if (!o) {
		fprintf(stderr,
			"Unable to parse object %s for remote ref %s\n",
			sha1_to_hex(ref->old_sha1), ls->dentry_name);
		aborted = 1;
		free(ref);
		return;
	}

	len = strlen(ls->dentry_name) + 42;
	ref_info = xcalloc(len + 1, 1);
	sprintf(ref_info, "%s	%s\n",
		sha1_to_hex(ref->old_sha1), ls->dentry_name);
	fwrite_buffer(ref_info, 1, len, buf);
	free(ref_info);

	if (o->type == OBJ_TAG) {
		o = deref_tag(o, ls->dentry_name, 0);
		if (o) {
			len = strlen(ls->dentry_name) + 45;
			ref_info = xcalloc(len + 1, 1);
			sprintf(ref_info, "%s	%s^{}\n",
				sha1_to_hex(o->sha1), ls->dentry_name);
			fwrite_buffer(ref_info, 1, len, buf);
			free(ref_info);
		}
	}
	free(ref);
}