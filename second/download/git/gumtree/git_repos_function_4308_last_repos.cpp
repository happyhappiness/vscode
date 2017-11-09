int get_sha1_commit(const char *name, unsigned char *sha1)
{
	struct object_context unused;
	return get_sha1_with_context(name, GET_SHA1_COMMIT,
				     sha1, &unused);
}