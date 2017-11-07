static int verify_tag(const char *name, const char *ref,
				const unsigned char *sha1)
{
	return gpg_verify_tag(sha1, name, GPG_VERIFY_VERBOSE);
}