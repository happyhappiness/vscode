void maybe_die_on_misspelt_object_name(const char *name, const char *prefix)
{
	struct object_context oc;
	unsigned char sha1[20];
	get_sha1_with_context_1(name, GET_SHA1_ONLY_TO_DIE, prefix, sha1, &oc);
}