static void *generate_fake_oid(const void *old, size_t *len)
{
	static uint32_t counter = 1; /* avoid null sha1 */
	unsigned char *out = xcalloc(GIT_SHA1_RAWSZ, 1);
	put_be32(out + GIT_SHA1_RAWSZ - 4, counter++);
	return out;
}