static int try_explicit_object_name(const char *name,
				    struct ref **match)
{
	struct object_id oid;

	if (!*name) {
		if (match)
			*match = alloc_delete_ref();
		return 0;
	}

	if (get_sha1(name, oid.hash))
		return -1;

	if (match) {
		*match = alloc_ref(name);
		oidcpy(&(*match)->new_oid, &oid);
	}
	return 0;
}