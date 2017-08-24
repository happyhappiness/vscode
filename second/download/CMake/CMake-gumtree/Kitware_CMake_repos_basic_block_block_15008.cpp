{
		/*
		 * If we don't know the UID is right, we can just check
		 * the user, since all systems set the file UID from
		 * the process UID.
		 */
		if (a->user_uid != a->uid) {
			mode &= ~ S_ISUID;
			if (a->flags & ARCHIVE_EXTRACT_OWNER) {
				archive_set_error(&a->archive, -1,
				    "Can't make file SUID");
				r = ARCHIVE_WARN;
			}
		}
		a->todo &= ~TODO_SUID_CHECK;
	}