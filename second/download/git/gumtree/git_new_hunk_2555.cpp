		}
	}

	/* Remove the "old-" files */
	for_each_string_list_item(item, &names) {
		for (ext = 0; ext < ARRAY_SIZE(exts); ext++) {
			char *fname;
			fname = mkpathdup("%s/old-%s%s",
					  packdir,
					  item->string,
					  exts[ext].name);
			if (remove_path(fname))
				warning(_("removing '%s' failed"), fname);
			free(fname);
		}
	}

	/* End of pack replacement. */

	if (delete_redundant) {
