int has_loose_object_nonlocal(const unsigned char *sha1)
{
	struct alternate_object_database *alt;
	prepare_alt_odb();
	for (alt = alt_odb_list; alt; alt = alt->next) {
		fill_sha1_path(alt->name, sha1);
		if (!access(alt->base, F_OK))
			return 1;
	}
	return 0;
}