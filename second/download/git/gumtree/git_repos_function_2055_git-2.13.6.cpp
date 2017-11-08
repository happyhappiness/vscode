char *odb_pack_name(struct strbuf *buf,
		     const unsigned char *sha1,
		     const char *ext)
{
	strbuf_reset(buf);
	strbuf_addf(buf, "%s/pack/pack-%s.%s", get_object_directory(),
		    sha1_to_hex(sha1), ext);
	return buf->buf;
}