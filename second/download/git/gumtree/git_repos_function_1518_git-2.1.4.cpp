static int has_loose_object(const unsigned char *sha1)
{
	return has_loose_object_local(sha1) ||
	       has_loose_object_nonlocal(sha1);
}