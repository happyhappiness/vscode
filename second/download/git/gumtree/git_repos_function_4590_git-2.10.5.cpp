static void show_one(const char *refname, const struct object_id *oid)
{
	const char *hex = find_unique_abbrev(oid->hash, abbrev);
	if (hash_only)
		printf("%s\n", hex);
	else
		printf("%s %s\n", hex, refname);
}