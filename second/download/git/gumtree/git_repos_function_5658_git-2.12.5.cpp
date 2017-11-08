static const unsigned char *anonymize_sha1(const unsigned char *sha1)
{
	static struct hashmap sha1s;
	size_t len = 20;
	return anonymize_mem(&sha1s, generate_fake_sha1, sha1, &len);
}