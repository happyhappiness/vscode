			return 0;
		refname++;
	}
	return 1;
}

char *resolve_refdup(const char *refname, int resolve_flags,
		     unsigned char *sha1, int *flags)
{
	return xstrdup_or_null(resolve_ref_unsafe(refname, resolve_flags,
						  sha1, flags));
}

/* The argument to filter_refs */
struct ref_filter {
	const char *pattern;
	each_ref_fn *fn;
	void *cb_data;
};

int read_ref_full(const char *refname, int resolve_flags, unsigned char *sha1, int *flags)
{
	if (resolve_ref_unsafe(refname, resolve_flags, sha1, flags))
		return 0;
	return -1;
}

int read_ref(const char *refname, unsigned char *sha1)
{
	return read_ref_full(refname, RESOLVE_REF_READING, sha1, NULL);
}

int ref_exists(const char *refname)
{
	unsigned char sha1[20];
	return !!resolve_ref_unsafe(refname, RESOLVE_REF_READING, sha1, NULL);
}

static int filter_refs(const char *refname, const struct object_id *oid,
			   int flags, void *data)
{
	struct ref_filter *filter = (struct ref_filter *)data;

	if (wildmatch(filter->pattern, refname, 0, NULL))
		return 0;
	return filter->fn(refname, oid, flags, filter->cb_data);
}

enum peel_status peel_object(const unsigned char *name, unsigned char *sha1)
{
	struct object *o = lookup_unknown_object(name);

	if (o->type == OBJ_NONE) {
		int type = sha1_object_info(name, NULL);
		if (type < 0 || !object_as_type(o, type, 0))
			return PEEL_INVALID;
	}

	if (o->type != OBJ_TAG)
		return PEEL_NON_TAG;

	o = deref_tag_noverify(o);
	if (!o)
		return PEEL_INVALID;

	hashcpy(sha1, o->oid.hash);
	return PEEL_PEELED;
}

struct warn_if_dangling_data {
	FILE *fp;
	const char *refname;
	const struct string_list *refnames;
	const char *msg_fmt;
};

static int warn_if_dangling_symref(const char *refname, const struct object_id *oid,
				   int flags, void *cb_data)
{
	struct warn_if_dangling_data *d = cb_data;
	const char *resolves_to;
	struct object_id junk;

	if (!(flags & REF_ISSYMREF))
		return 0;

	resolves_to = resolve_ref_unsafe(refname, 0, junk.hash, NULL);
	if (!resolves_to
	    || (d->refname
		? strcmp(resolves_to, d->refname)
		: !string_list_has_string(d->refnames, resolves_to))) {
		return 0;
	}

	fprintf(d->fp, d->msg_fmt, refname);
	fputc('\n', d->fp);
	return 0;
}

void warn_dangling_symref(FILE *fp, const char *msg_fmt, const char *refname)
{
	struct warn_if_dangling_data data;

	data.fp = fp;
	data.refname = refname;
	data.refnames = NULL;
	data.msg_fmt = msg_fmt;
	for_each_rawref(warn_if_dangling_symref, &data);
}

void warn_dangling_symrefs(FILE *fp, const char *msg_fmt, const struct string_list *refnames)
{
	struct warn_if_dangling_data data;

	data.fp = fp;
	data.refname = NULL;
	data.refnames = refnames;
	data.msg_fmt = msg_fmt;
	for_each_rawref(warn_if_dangling_symref, &data);
}

int for_each_tag_ref(each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in("refs/tags/", fn, cb_data);
}

int for_each_tag_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in_submodule(submodule, "refs/tags/", fn, cb_data);
}

int for_each_branch_ref(each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in("refs/heads/", fn, cb_data);
}

int for_each_branch_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in_submodule(submodule, "refs/heads/", fn, cb_data);
}

int for_each_remote_ref(each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in("refs/remotes/", fn, cb_data);
}

int for_each_remote_ref_submodule(const char *submodule, each_ref_fn fn, void *cb_data)
{
	return for_each_ref_in_submodule(submodule, "refs/remotes/", fn, cb_data);
}

int head_ref_namespaced(each_ref_fn fn, void *cb_data)
{
	struct strbuf buf = STRBUF_INIT;
	int ret = 0;
	struct object_id oid;
	int flag;

	strbuf_addf(&buf, "%sHEAD", get_git_namespace());
	if (!read_ref_full(buf.buf, RESOLVE_REF_READING, oid.hash, &flag))
		ret = fn(buf.buf, &oid, flag, cb_data);
	strbuf_release(&buf);

	return ret;
}

int for_each_glob_ref_in(each_ref_fn fn, const char *pattern,
	const char *prefix, void *cb_data)
{
	struct strbuf real_pattern = STRBUF_INIT;
	struct ref_filter filter;
	int ret;

	if (!prefix && !starts_with(pattern, "refs/"))
		strbuf_addstr(&real_pattern, "refs/");
	else if (prefix)
		strbuf_addstr(&real_pattern, prefix);
	strbuf_addstr(&real_pattern, pattern);

	if (!has_glob_specials(pattern)) {
		/* Append implied '/' '*' if not present. */
		strbuf_complete(&real_pattern, '/');
		/* No need to check for '*', there is none. */
		strbuf_addch(&real_pattern, '*');
	}

	filter.pattern = real_pattern.buf;
	filter.fn = fn;
	filter.cb_data = cb_data;
	ret = for_each_ref(filter_refs, &filter);
