int get_sha1_mb(const char *name, unsigned char *sha1)
{
	struct commit *one, *two;
	struct commit_list *mbs;
	unsigned char sha1_tmp[20];
	const char *dots;
	int st;

	dots = strstr(name, "...");
	if (!dots)
		return get_sha1(name, sha1);
	if (dots == name)
		st = get_sha1("HEAD", sha1_tmp);
	else {
		struct strbuf sb;
		strbuf_init(&sb, dots - name);
		strbuf_add(&sb, name, dots - name);
		st = get_sha1_committish(sb.buf, sha1_tmp);
		strbuf_release(&sb);
	}
	if (st)
		return st;
	one = lookup_commit_reference_gently(sha1_tmp, 0);
	if (!one)
		return -1;

	if (get_sha1_committish(dots[3] ? (dots + 3) : "HEAD", sha1_tmp))
		return -1;
	two = lookup_commit_reference_gently(sha1_tmp, 0);
	if (!two)
		return -1;
	mbs = get_merge_bases(one, two);
	if (!mbs || mbs->next)
		st = -1;
	else {
		st = 0;
		hashcpy(sha1, mbs->item->object.sha1);
	}
	free_commit_list(mbs);
	return st;
}