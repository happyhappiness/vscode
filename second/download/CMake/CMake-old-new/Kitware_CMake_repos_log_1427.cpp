archive_set_error(&a->archive, t->tree_errno,
				    "%ls: Cannot stat",
				    tree_current_path(t))