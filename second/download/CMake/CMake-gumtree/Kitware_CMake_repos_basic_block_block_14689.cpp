(errno == EOPNOTSUPP) {
			/* Filesystem doesn't support ACLs */
			ret = ARCHIVE_OK;
		} else {
			archive_set_error(a, errno, "Failed to set %s acl",
			    tname);
			ret = ARCHIVE_WARN;
		}