archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "%s: Couldn't visit directory",
			    tree_current_path(t));