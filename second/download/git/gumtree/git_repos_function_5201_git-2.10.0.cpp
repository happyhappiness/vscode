static void add_branch_description(struct strbuf *buf, const char *branch_name)
{
	struct strbuf desc = STRBUF_INIT;
	if (!branch_name || !*branch_name)
		return;
	read_branch_desc(&desc, branch_name);
	if (desc.len) {
		strbuf_addch(buf, '\n');
		strbuf_addbuf(buf, &desc);
		strbuf_addch(buf, '\n');
	}
	strbuf_release(&desc);
}