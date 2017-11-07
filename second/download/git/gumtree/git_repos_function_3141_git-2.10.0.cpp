static void hostinfo_init(struct hostinfo *hi)
{
	memset(hi, 0, sizeof(*hi));
	strbuf_init(&hi->hostname, 0);
	strbuf_init(&hi->canon_hostname, 0);
	strbuf_init(&hi->ip_address, 0);
	strbuf_init(&hi->tcp_port, 0);
}