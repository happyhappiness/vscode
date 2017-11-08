static int read_remote_branches(const char *refname,
	const struct object_id *oid, int flags, void *cb_data)
{
	struct rename_info *rename = cb_data;
	struct strbuf buf = STRBUF_INIT;
	struct string_list_item *item;
	int flag;
	struct object_id orig_oid;
	const char *symref;

	strbuf_addf(&buf, "refs/remotes/%s/", rename->old);
	if (starts_with(refname, buf.buf)) {
		item = string_list_append(rename->remote_branches, xstrdup(refname));
		symref = resolve_ref_unsafe(refname, RESOLVE_REF_READING,
					    orig_oid.hash, &flag);
		if (flag & REF_ISSYMREF)
			item->util = xstrdup(symref);
		else
			item->util = NULL;
	}

	return 0;
}