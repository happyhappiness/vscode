static int delete_replace_ref(const char *name, const char *ref,
			      const unsigned char *sha1)
{
	if (delete_ref(ref, sha1, 0))
		return 1;
	printf("Deleted replace ref '%s'\n", name);
	return 0;
}