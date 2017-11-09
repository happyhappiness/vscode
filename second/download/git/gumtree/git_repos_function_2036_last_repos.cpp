static unsigned int hash_obj(const unsigned char *sha1, unsigned int n)
{
	return sha1hash(sha1) & (n - 1);
}