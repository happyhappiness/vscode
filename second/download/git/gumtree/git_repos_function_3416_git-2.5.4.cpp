int strbuf_branchname(struct strbuf *sb, const char *name)
{
	int len = strlen(name);
	int used = interpret_branch_name(name, len, sb);

	if (used == len)
		return 0;
	if (used < 0)
		used = 0;
	strbuf_add(sb, name + used, len - used);
	return len;
}