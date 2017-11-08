char *sha1_pack_index_name(const unsigned char *sha1)
{
	static char *name, *base;

	return sha1_get_pack_name(sha1, &name, &base, "idx");
}