int get_sha1_with_context(const char *str, unsigned flags, unsigned char *sha1, struct object_context *oc)
{
	if (flags & GET_SHA1_FOLLOW_SYMLINKS && flags & GET_SHA1_ONLY_TO_DIE)
		die("BUG: incompatible flags for get_sha1_with_context");
	return get_sha1_with_context_1(str, flags, NULL, sha1, oc);
}