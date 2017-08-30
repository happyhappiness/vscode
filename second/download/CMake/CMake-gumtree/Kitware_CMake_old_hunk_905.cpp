			a->archive.state = ARCHIVE_STATE_FATAL;

			return (ARCHIVE_FATAL);

		case TREE_ERROR_DIR:

			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

			    "%ls: Couldn't visit directory",

			    tree_current_path(t));

			return (ARCHIVE_FAILED);

