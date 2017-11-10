static void construct_path_with_fanout(const unsigned char *sha1,
		unsigned char fanout, char *path)
{
	unsigned int i = 0, j = 0;
	const char *hex_sha1 = sha1_to_hex(sha1);
	assert(fanout < 20);
	while (fanout) {
		path[i++] = hex_sha1[j++];
		path[i++] = hex_sha1[j++];
		path[i++] = '/';
		fanout--;
	}
	strcpy(path + i, hex_sha1 + j);
}