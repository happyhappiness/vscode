static int delete_replace_ref(const char *name, const char *ref,
			      const struct object_id *oid)
{
	if (delete_ref(NULL, ref, oid->hash, 0))
		return 1;
	printf("Deleted replace ref '%s'\n", name);
	return 0;
}