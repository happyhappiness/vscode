int get_sha1_committish(const char *name, unsigned char *sha1)
{
	struct object_context unused;
	return get_sha1_with_context(name, GET_SHA1_COMMITTISH,
				     sha1, &unused);
}