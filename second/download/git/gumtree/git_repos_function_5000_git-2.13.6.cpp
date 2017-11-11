static void commit_info_destroy(struct commit_info *ci)
{

	strbuf_release(&ci->author);
	strbuf_release(&ci->author_mail);
	strbuf_release(&ci->author_tz);
	strbuf_release(&ci->committer);
	strbuf_release(&ci->committer_mail);
	strbuf_release(&ci->committer_tz);
	strbuf_release(&ci->summary);
}