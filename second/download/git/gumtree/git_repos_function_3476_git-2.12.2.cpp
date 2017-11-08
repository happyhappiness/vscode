static int append_sha1_to_argv(const unsigned char sha1[20], void *data)
{
	struct argv_array *argv = data;
	argv_array_push(argv, sha1_to_hex(sha1));
	return 0;
}