(errno == ENOTSUP || errno == ENOSYS) {
					if (!warning_done) {
						warning_done = 1;
						archive_set_error(&a->archive,
						    errno,
						    "Cannot restore extended "
						    "attributes on this file "
						    "system");
					}
				} else
					archive_set_error(&a->archive, errno,
					    "Failed to set extended attribute")