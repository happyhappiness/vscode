static int try_explicit_object_name(const char *name,
				    struct ref **match)
{
	unsigned char sha1[20];

	if (!*name) {
		if (match)
			*match = alloc_delete_ref();
		return 0;
	}

	if (get_sha1(name, sha1))
		return -1;

	if (match) {
		*match = alloc_ref(name);
		hashcpy((*match)->new_sha1, sha1);
	}
	return 0;
}