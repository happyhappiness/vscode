(a->flags & ARCHIVE_EXTRACT_OWNER) {
				/*
				 * This is only an error if you
				 * requested owner restore.  If you
				 * didn't, we'll try to restore
				 * sgid/suid, but won't consider it a
				 * problem if we can't.
				 */
				archive_set_error(&a->archive, -1,
				    "Can't restore SGID bit");
				r = ARCHIVE_WARN;
			}