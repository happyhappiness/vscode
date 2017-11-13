static int delete_tag(const char *name, const char *ref,
		      const unsigned char *sha1, const void *cb_data)
{
	if (delete_ref(NULL, ref, sha1, 0))
		return 1;
	printf(_("Deleted tag '%s' (was %s)\n"), name, find_unique_abbrev(sha1, DEFAULT_ABBREV));
	return 0;
}