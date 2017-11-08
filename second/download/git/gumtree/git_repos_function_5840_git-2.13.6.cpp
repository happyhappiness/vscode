static const unsigned char *anonymize_sha1(const struct object_id *oid)
{
	static struct hashmap sha1s;
	size_t len = GIT_SHA1_RAWSZ;
	return anonymize_mem(&sha1s, generate_fake_oid, oid, &len);
}