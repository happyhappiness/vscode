static void show_one(const char *refname, const unsigned char *sha1)
{
	const char *hex = find_unique_abbrev(sha1, abbrev);
	if (hash_only)
		printf("%s\n", hex);
	else
		printf("%s %s\n", hex, refname);
}