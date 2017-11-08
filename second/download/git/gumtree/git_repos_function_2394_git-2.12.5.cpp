void setup_mailinfo(struct mailinfo *mi)
{
	memset(mi, 0, sizeof(*mi));
	strbuf_init(&mi->name, 0);
	strbuf_init(&mi->email, 0);
	strbuf_init(&mi->charset, 0);
	strbuf_init(&mi->log_message, 0);
	strbuf_init(&mi->inbody_header_accum, 0);
	mi->header_stage = 1;
	mi->use_inbody_headers = 1;
	mi->content_top = mi->content;
	git_config(git_mailinfo_config, mi);
}