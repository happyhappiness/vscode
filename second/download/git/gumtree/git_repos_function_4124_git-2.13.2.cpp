static void find_short_object_filename(struct disambiguate_state *ds)
{
	struct alternate_object_database *alt;
	char hex[GIT_MAX_HEXSZ];
	static struct alternate_object_database *fakeent;

	if (!fakeent) {
		/*
		 * Create a "fake" alternate object database that
		 * points to our own object database, to make it
		 * easier to get a temporary working space in
		 * alt->name/alt->base while iterating over the
		 * object databases including our own.
		 */
		fakeent = alloc_alt_odb(get_object_directory());
	}
	fakeent->next = alt_odb_list;

	xsnprintf(hex, sizeof(hex), "%.2s", ds->hex_pfx);
	for (alt = fakeent; alt && !ds->ambiguous; alt = alt->next) {
		struct strbuf *buf = alt_scratch_buf(alt);
		struct dirent *de;
		DIR *dir;

		strbuf_addf(buf, "%.2s/", ds->hex_pfx);
		dir = opendir(buf->buf);
		if (!dir)
			continue;

		while (!ds->ambiguous && (de = readdir(dir)) != NULL) {
			struct object_id oid;

			if (strlen(de->d_name) != GIT_SHA1_HEXSZ - 2)
				continue;
			if (memcmp(de->d_name, ds->hex_pfx + 2, ds->len - 2))
				continue;
			memcpy(hex + 2, de->d_name, GIT_SHA1_HEXSZ - 2);
			if (!get_oid_hex(hex, &oid))
				update_candidates(ds, &oid);
		}
		closedir(dir);
	}
}