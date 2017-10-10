	strbuf_addf(&buf, "%s.%lu.git.%s", base,
		    (unsigned long) time(NULL),
		    git_committer_info(IDENT_NO_NAME|IDENT_NO_DATE|IDENT_STRICT));
	info->message_id = strbuf_detach(&buf, NULL);
}

static void print_signature(void)
{
	if (!signature || !*signature)
		return;

	printf("-- \n%s", signature);
	if (signature[strlen(signature)-1] != '\n')
		putchar('\n');
	putchar('\n');
}

static void add_branch_description(struct strbuf *buf, const char *branch_name)
{
	struct strbuf desc = STRBUF_INIT;
	if (!branch_name || !*branch_name)
