const char *sha1_file_name(const unsigned char *sha1)
{
	static struct strbuf buf = STRBUF_INIT;

	strbuf_reset(&buf);
	strbuf_addf(&buf, "%s/", get_object_directory());

	fill_sha1_path(&buf, sha1);
	return buf.buf;
}