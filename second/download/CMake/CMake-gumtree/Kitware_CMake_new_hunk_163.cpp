				archive_set_error(&a->archive,

				    ARCHIVE_ERRNO_MISC,

				    "Invalid Rockridge RE");

				goto fail;

			}

		} else if (parent != NULL && parent->rr_moved)

			file->rr_moved_has_re_only = 0;

