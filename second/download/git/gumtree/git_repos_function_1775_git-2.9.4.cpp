static char *sha1_get_pack_name(const unsigned char *sha1,
				struct strbuf *buf,
				const char *which)
{
	strbuf_reset(buf);
	strbuf_addf(buf, "%s/pack/pack-%s.%s", get_object_directory(),
		    sha1_to_hex(sha1), which);
	return buf->buf;
}