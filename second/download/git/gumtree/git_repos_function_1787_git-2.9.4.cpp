static int check_and_freshen_nonlocal(const unsigned char *sha1, int freshen)
{
	struct alternate_object_database *alt;
	prepare_alt_odb();
	for (alt = alt_odb_list; alt; alt = alt->next) {
		fill_sha1_path(alt->name, sha1);
		if (check_and_freshen_file(alt->base, freshen))
			return 1;
	}
	return 0;
}