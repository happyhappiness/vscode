static void show_one(const char *refname, const struct object_id *oid)
{
	const char *hex;
	struct object_id peeled;

	if (!has_sha1_file(oid->hash))
		die("git show-ref: bad ref %s (%s)", refname,
		    oid_to_hex(oid));

	if (quiet)
		return;

	hex = find_unique_abbrev(oid->hash, abbrev);
	if (hash_only)
		printf("%s\n", hex);
	else
		printf("%s %s\n", hex, refname);

	if (!deref_tags)
		return;

	if (!peel_ref(refname, peeled.hash)) {
		hex = find_unique_abbrev(peeled.hash, abbrev);
		printf("%s %s^{}\n", hex, refname);
	}
}