archive_set_error(&a->archive, errno,
				    "%ls: Cannot stat",
				    tree_current_path(t));