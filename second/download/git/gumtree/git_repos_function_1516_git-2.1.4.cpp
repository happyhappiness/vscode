static int has_loose_object_local(const unsigned char *sha1)
{
	return !access(sha1_file_name(sha1), F_OK);
}