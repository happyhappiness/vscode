int strbuf_check_branch_ref(struct strbuf *sb, const char *name)
{
	strbuf_branchname(sb, name, INTERPRET_BRANCH_LOCAL);
	if (name[0] == '-')
		return -1;
	strbuf_splice(sb, 0, 0, "refs/heads/", 11);
	return check_refname_format(sb->buf, 0);
}