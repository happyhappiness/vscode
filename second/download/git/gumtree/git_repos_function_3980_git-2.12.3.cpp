static int collect_ambiguous(const unsigned char *sha1, void *data)
{
	sha1_array_append(data, sha1);
	return 0;
}