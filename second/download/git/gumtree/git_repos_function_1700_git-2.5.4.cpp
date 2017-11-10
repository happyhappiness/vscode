static int freshen_loose_object(const unsigned char *sha1)
{
	return check_and_freshen(sha1, 1);
}