{
			mode &= ~ S_ISUID;
			if (a->flags & ARCHIVE_EXTRACT_OWNER) {
				archive_set_error(&a->archive, -1,
				    "Can't make file SUID");
				r = ARCHIVE_WARN;
			}
		}