static const char *derive_filename(const char *pack_name, const char *suffix,
				   struct strbuf *buf)
{
	size_t len;
	if (!strip_suffix(pack_name, ".pack", &len))
		die(_("packfile name '%s' does not end with '.pack'"),
		    pack_name);
	strbuf_add(buf, pack_name, len);
	strbuf_addstr(buf, suffix);
	return buf->buf;
}