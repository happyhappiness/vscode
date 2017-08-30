		}	
	} while (lst == NULL);

#ifdef __APPLE__
	if (a->enable_copyfile) {
		/* If we're using copyfile(), ignore "._XXX" files. */
		const char *bname = strrchr(tree_current_path(t), '/');
		if (bname == NULL)
			bname = tree_current_path(t);
		else
			++bname;
		if (bname[0] == '.' && bname[1] == '_')
			return (ARCHIVE_RETRY);
	}
#endif

	archive_entry_copy_pathname(entry, tree_current_path(t));
	/*
	 * Perform path matching.
	 */
	if (a->matching) {
		r = archive_match_path_excluded(a->matching, entry);
		if (r < 0) {
			archive_set_error(&(a->archive), errno,
			    "Faild : %s", archive_error_string(a->matching));
			return (r);
		}
		if (r) {
			if (a->excluded_cb_func)
				a->excluded_cb_func(&(a->archive),
				    a->excluded_cb_data, entry);
			return (ARCHIVE_RETRY);
		}
	}

	/*
	 * Distinguish 'L'/'P'/'H' symlink following.
	 */
