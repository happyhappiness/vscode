static void commit_info_init(struct commit_info *ci)
{

	strbuf_init(&ci->author, 0);
	strbuf_init(&ci->author_mail, 0);
	strbuf_init(&ci->author_tz, 0);
	strbuf_init(&ci->committer, 0);
	strbuf_init(&ci->committer_mail, 0);
	strbuf_init(&ci->committer_tz, 0);
	strbuf_init(&ci->summary, 0);
}