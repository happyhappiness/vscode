int has_sha1_file(const unsigned char *sha1)
{
	struct pack_entry e;

	if (find_pack_entry(sha1, &e))
		return 1;
	if (has_loose_object(sha1))
		return 1;
	reprepare_packed_git();
	return find_pack_entry(sha1, &e);
}