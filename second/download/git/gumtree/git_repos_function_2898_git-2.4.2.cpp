static void add_sha1_to_argv(const unsigned char sha1[20], void *data)
{
	argv_array_push(data, sha1_to_hex(sha1));
}