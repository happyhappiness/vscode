static void find_short_object_filename(int len, const char *hex_pfx, struct disambiguate_state *ds)
{
	struct alternate_object_database *alt;
	char hex[40];
	static struct alternate_object_database *fakeent;

	if (!fakeent) {
		/*
		 * Create a "fake" alternate object database that
		 * points to our own object database, to make it
		 * easier to get a temporary working space in
		 * alt->name/alt->base while iterating over the
		 * object databases including our own.
		 */
		const char *objdir = get_object_directory();
		int objdir_len = strlen(objdir);
		int entlen = objdir_len + 43;
		fakeent = xmalloc(sizeof(*fakeent) + entlen);
		memcpy(fakeent->base, objdir, objdir_len);
		fakeent->name = fakeent->base + objdir_len + 1;
		fakeent->name[-1] = '/';
	}
	fakeent->next = alt_odb_list;

	sprintf(hex, "%.2s", hex_pfx);
	for (alt = fakeent; alt && !ds->ambiguous; alt = alt->next) {
		struct dirent *de;
		DIR *dir;
		sprintf(alt->name, "%.2s/", hex_pfx);
		dir = opendir(alt->base);
		if (!dir)
			continue;

		while (!ds->ambiguous && (de = readdir(dir)) != NULL) {
			unsigned char sha1[20];

			if (strlen(de->d_name) != 38)
				continue;
			if (memcmp(de->d_name, hex_pfx + 2, len - 2))
				continue;
			memcpy(hex + 2, de->d_name, 38);
			if (!get_sha1_hex(hex, sha1))
				update_candidates(ds, sha1);
		}
		closedir(dir);
	}
}