(name != NULL) {
			int e;
			int namespace;

			if (strncmp(name, "user.", 5) == 0) {
				/* "user." attributes go to user namespace */
				name += 5;
				namespace = EXTATTR_NAMESPACE_USER;
			} else {
				/* Warn about other extended attributes. */
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Can't restore extended attribute ``%s''",
				    name);
				ret = ARCHIVE_WARN;
				continue;
			}
			errno = 0;
#if HAVE_EXTATTR_SET_FD
			if (a->fd >= 0)
				e = extattr_set_fd(a->fd, namespace, name,
				    value, size);
			else
#endif
			/* TODO: should we use extattr_set_link() instead? */
			{
				e = extattr_set_file(
				    archive_entry_pathname(entry), namespace,
				    name, value, size);
			}
			if (e != (int)size) {
				if (errno == ENOTSUP || errno == ENOSYS) {
					if (!warning_done) {
						warning_done = 1;
						archive_set_error(&a->archive,
						    errno,
						    "Cannot restore extended "
						    "attributes on this file "
						    "system");
					}
				} else {
					archive_set_error(&a->archive, errno,
					    "Failed to set extended attribute");
				}

				ret = ARCHIVE_WARN;
			}
		}