char *sha1_pack_index_name(const unsigned char *sha1)
{
	static struct strbuf buf = STRBUF_INIT;
	return sha1_get_pack_name(sha1, &buf, "idx");
}