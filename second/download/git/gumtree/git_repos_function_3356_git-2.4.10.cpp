int get_sha1_with_context(const char *str, unsigned flags, unsigned char *sha1, struct object_context *orc)
{
	return get_sha1_with_context_1(str, flags, NULL, sha1, orc);
}