{
				archive_set_error(&a->archive, errno,
				    "%s: Cannot stat",
				    tree_current_path(t));
				tree_enter_initial_dir(t);
				return (ARCHIVE_FAILED);
			}