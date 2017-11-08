static const char *alt_sha1_path(struct alternate_object_database *alt,
				 const unsigned char *sha1)
{
	struct strbuf *buf = alt_scratch_buf(alt);
	fill_sha1_path(buf, sha1);
	return buf->buf;
}