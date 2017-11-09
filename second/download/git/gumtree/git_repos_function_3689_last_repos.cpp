static void hostinfo_clear(struct hostinfo *hi)
{
	strbuf_release(&hi->hostname);
	strbuf_release(&hi->canon_hostname);
	strbuf_release(&hi->ip_address);
	strbuf_release(&hi->tcp_port);
}