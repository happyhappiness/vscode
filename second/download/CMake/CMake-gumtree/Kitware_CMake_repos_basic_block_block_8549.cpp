((flags & ARCHIVE_ENTRY_ACL_STYLE_SOLARIS) != 0) {
			/* "user::rwx\ngroup::rwx\nother:rwx\n" */
			length += 31;
		} else {
			/* "user::rwx\ngroup::rwx\nother::rwx\n" */
			length += 32;
		}