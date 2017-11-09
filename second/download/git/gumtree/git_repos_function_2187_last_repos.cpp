static int check_and_freshen(const unsigned char *sha1, int freshen)
{
	return check_and_freshen_local(sha1, freshen) ||
	       check_and_freshen_nonlocal(sha1, freshen);
}