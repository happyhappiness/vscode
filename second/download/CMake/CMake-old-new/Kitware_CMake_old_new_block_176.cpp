{
				err = r;
				if (err == ARCHIVE_FATAL) {
					archive_set_error(&a->archive, ENOMEM,
					    "Can't allocate memory for "
					    "SCHILY.acl.default");
					return (err);
				}
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Parse error: SCHILY.acl.default");
			}