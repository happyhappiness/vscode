(tree_next(t)) {
		case TREE_ERROR_FATAL:
			archive_set_error(&a->archive, t->tree_errno,
			    "%ls: Unable to continue traversing directory tree",
			    tree_current_path(t));
			a->archive.state = ARCHIVE_STATE_FATAL;
			return (ARCHIVE_FATAL);
		case TREE_ERROR_DIR:
			archive_set_error(&a->archive, t->tree_errno,
			    "%ls: Couldn't visit directory",
			    tree_current_path(t));
			return (ARCHIVE_FAILED);
		case 0:
			return (ARCHIVE_EOF);
		case TREE_POSTDESCENT:
		case TREE_POSTASCENT:
			break;
		case TREE_REGULAR:
			lst = tree_current_lstat(t);
			if (lst == NULL) {
				archive_set_error(&a->archive, t->tree_errno,
				    "%ls: Cannot stat",
				    tree_current_path(t));
				return (ARCHIVE_FAILED);
			}
			break;
		}