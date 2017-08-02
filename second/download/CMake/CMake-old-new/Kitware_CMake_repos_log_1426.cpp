archive_set_error(&a->archive, t->tree_errno,
			    "%ls: Couldn't visit directory",
			    tree_current_path(t))