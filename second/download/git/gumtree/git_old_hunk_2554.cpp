	 * if we can move them out of the way (this can happen if we
	 * repacked immediately after packing fully.
	 */
	failed = 0;
	for_each_string_list_item(item, &names) {
		for (ext = 0; ext < ARRAY_SIZE(exts); ext++) {
			const char *fname_old;
			char *fname;
			fname = mkpathdup("%s/pack-%s%s", packdir,
						item->string, exts[ext].name);
			if (!file_exists(fname)) {
				free(fname);
				continue;
			}

			fname_old = mkpath("%s/old-%s%s", packdir,
						item->string, exts[ext].name);
			if (file_exists(fname_old))
				if (unlink(fname_old))
					failed = 1;

			if (!failed && rename(fname, fname_old)) {
				free(fname);
				failed = 1;
				break;
			} else {
				string_list_append(&rollback, fname);
			}
		}
		if (failed)
			break;
	}
	if (failed) {
		struct string_list rollback_failure = STRING_LIST_INIT_DUP;
		for_each_string_list_item(item, &rollback) {
			const char *fname_old;
			char *fname;
			fname = mkpathdup("%s/%s", packdir, item->string);
			fname_old = mkpath("%s/old-%s", packdir, item->string);
			if (rename(fname_old, fname))
				string_list_append(&rollback_failure, fname);
			free(fname);
		}

		if (rollback_failure.nr) {
			int i;
			fprintf(stderr,
				"WARNING: Some packs in use have been renamed by\n"
