static int check_and_freshen_local(const unsigned char *sha1, int freshen)
{
	return check_and_freshen_file(sha1_file_name(sha1), freshen);
}