static int get_current_sha1(const char *path, unsigned char *sha1)
{
	int pos;

	if (read_cache() < 0)
		return -1;
	pos = cache_name_pos(path, strlen(path));
	if (pos < 0)
		return -1;
	hashcpy(sha1, active_cache[pos]->sha1);
	return 0;
}