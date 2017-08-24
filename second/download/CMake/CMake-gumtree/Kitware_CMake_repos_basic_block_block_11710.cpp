(parent == NULL || parent->rr_moved == 0) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Invalid Rockridge RE");
				goto fail;
			}