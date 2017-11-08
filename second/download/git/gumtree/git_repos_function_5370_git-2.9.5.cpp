static void *generate_fake_sha1(const void *old, size_t *len)
{
	static uint32_t counter = 1; /* avoid null sha1 */
	unsigned char *out = xcalloc(20, 1);
	put_be32(out + 16, counter++);
	return out;
}