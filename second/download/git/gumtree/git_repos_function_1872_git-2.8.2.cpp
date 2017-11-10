int has_sha1_file_with_flags(const unsigned char *sha1, int flags)
{
	struct pack_entry e;

	if (find_pack_entry(sha1, &e))
		return 1;
	if (has_loose_object(sha1))
		return 1;
	if (flags & HAS_SHA1_QUICK)
		return 0;
	reprepare_packed_git();
	return find_pack_entry(sha1, &e);
}