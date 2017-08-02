archive_set_error(&a->archive, t->tree_errno,
			    "%s: Unable to continue traversing directory tree",
			    tree_current_path(t))