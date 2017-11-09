int has_loose_object_nonlocal(const unsigned char *sha1)
{
	return check_and_freshen_nonlocal(sha1, 0);
}