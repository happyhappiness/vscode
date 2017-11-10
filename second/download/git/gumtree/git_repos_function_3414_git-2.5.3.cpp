int get_sha1(const char *name, unsigned char *sha1)
{
	struct object_context unused;
	return get_sha1_with_context(name, 0, sha1, &unused);
}