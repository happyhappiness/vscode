int get_oid_mb(const char *name, struct object_id *oid)
{
	struct commit *one, *two;
	struct commit_list *mbs;
	struct object_id oid_tmp;
	const char *dots;
	int st;

	dots = strstr(name, "...");
	if (!dots)
		return get_oid(name, oid);
	if (dots == name)
		st = get_oid("HEAD", &oid_tmp);
	else {
		struct strbuf sb;
		strbuf_init(&sb, dots - name);
		strbuf_add(&sb, name, dots - name);
		st = get_sha1_committish(sb.buf, oid_tmp.hash);
		strbuf_release(&sb);
	}
	if (st)
		return st;
	one = lookup_commit_reference_gently(&oid_tmp, 0);
	if (!one)
		return -1;

	if (get_sha1_committish(dots[3] ? (dots + 3) : "HEAD", oid_tmp.hash))
		return -1;
	two = lookup_commit_reference_gently(&oid_tmp, 0);
	if (!two)
		return -1;
	mbs = get_merge_bases(one, two);
	if (!mbs || mbs->next)
		st = -1;
	else {
		st = 0;
		oidcpy(oid, &mbs->item->object.oid);
	}
	free_commit_list(mbs);
	return st;
}