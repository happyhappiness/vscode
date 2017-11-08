static void gen_message_id(struct rev_info *info, char *base)
{
	struct strbuf buf = STRBUF_INIT;
	strbuf_addf(&buf, "%s.%lu.git.%s", base,
		    (unsigned long) time(NULL),
		    git_committer_info(IDENT_NO_NAME|IDENT_NO_DATE|IDENT_STRICT));
	info->message_id = strbuf_detach(&buf, NULL);
}