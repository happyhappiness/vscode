static unsigned long expand_name_field(struct strbuf *name, const char *cp_)
{
	const unsigned char *ep, *cp = (const unsigned char *)cp_;
	size_t len = decode_varint(&cp);

	if (name->len < len)
		die("malformed name field in the index");
	strbuf_remove(name, name->len - len, len);
	for (ep = cp; *ep; ep++)
		; /* find the end */
	strbuf_add(name, cp, ep - cp);
	return (const char *)ep + 1 - cp_;
}