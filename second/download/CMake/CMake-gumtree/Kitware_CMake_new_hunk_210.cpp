					archive_set_error(&a->archive,
					    ARCHIVE_ERRNO_MISC,
					    "Invalid Rockridge CL");
					goto fail;
				}
			}
			if (file->cl_offset == file->offset ||
			    parent->rr_moved) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Invalid Rockridge CL");
				goto fail;
			}
		}
	}
