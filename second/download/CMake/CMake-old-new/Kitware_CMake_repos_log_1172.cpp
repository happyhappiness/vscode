archive_set_error(&a->archive, errno,
				    "%s: Cannot stat",
				    tree_current_path(t))