static int add_sha1_to_array(const char *ref, const unsigned char *sha1,
			     int flags, void *data)
{
	sha1_array_append(data, sha1);
	return 0;
}