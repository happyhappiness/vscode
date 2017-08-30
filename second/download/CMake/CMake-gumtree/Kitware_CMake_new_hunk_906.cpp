		case TREE_REGULAR:

			lst = tree_current_lstat(t);

			if (lst == NULL) {

				archive_set_error(&a->archive, t->tree_errno,

				    "%ls: Cannot stat",

				    tree_current_path(t));

				return (ARCHIVE_FAILED);

