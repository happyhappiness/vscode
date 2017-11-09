static void construct_path_with_fanout(const unsigned char *sha1,
		unsigned char fanout, char *path)
{
	unsigned int i = 0, j = 0;
	const char *hex_sha1 = sha1_to_hex(sha1);
	assert(fanout < GIT_SHA1_RAWSZ);
	while (fanout) {
		path[i++] = hex_sha1[j++];
		path[i++] = hex_sha1[j++];
		path[i++] = '/';
		fanout--;
	}
	xsnprintf(path + i, FANOUT_PATH_MAX - i, "%s", hex_sha1 + j);
}