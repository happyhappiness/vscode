static struct stream_filter *ident_filter(const unsigned char *sha1)
{
	struct ident_filter *ident = xmalloc(sizeof(*ident));

	xsnprintf(ident->ident, sizeof(ident->ident),
		  ": %s $", sha1_to_hex(sha1));
	strbuf_init(&ident->left, 0);
	ident->filter.vtbl = &ident_vtbl;
	ident->state = 0;
	return (struct stream_filter *)ident;
}