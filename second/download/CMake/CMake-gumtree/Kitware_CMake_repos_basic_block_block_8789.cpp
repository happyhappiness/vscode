{
	case ARCHIVE_ENTRY_LINKIFY_LIKE_TAR:
		le = find_entry(res, *e);
		if (le != NULL) {
			archive_entry_unset_size(*e);
			archive_entry_copy_hardlink(*e,
			    archive_entry_pathname(le->canonical));
		} else
			insert_entry(res, *e);
		return;
	case ARCHIVE_ENTRY_LINKIFY_LIKE_MTREE:
		le = find_entry(res, *e);
		if (le != NULL) {
			archive_entry_copy_hardlink(*e,
			    archive_entry_pathname(le->canonical));
		} else
			insert_entry(res, *e);
		return;
	case ARCHIVE_ENTRY_LINKIFY_LIKE_OLD_CPIO:
		/* This one is trivial. */
		return;
	case ARCHIVE_ENTRY_LINKIFY_LIKE_NEW_CPIO:
		le = find_entry(res, *e);
		if (le != NULL) {
			/*
			 * Put the new entry in le, return the
			 * old entry from le.
			 */
			t = *e;
			*e = le->entry;
			le->entry = t;
			/* Make the old entry into a hardlink. */
			archive_entry_unset_size(*e);
			archive_entry_copy_hardlink(*e,
			    archive_entry_pathname(le->canonical));
			/* If we ran out of links, return the
			 * final entry as well. */
			if (le->links == 0) {
				*f = le->entry;
				le->entry = NULL;
			}
		} else {
			/*
			 * If we haven't seen it, tuck it away
			 * for future use.
			 */
			le = insert_entry(res, *e);
			if (le == NULL)
				/* XXX We should return an error code XXX */
				return;
			le->entry = *e;
			*e = NULL;
		}
		return;
	default:
		break;
	}