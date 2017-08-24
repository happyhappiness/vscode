(iso9660->seenRockridge) {
		if (parent != NULL && parent->parent == NULL &&
		    (flags & 0x02) && iso9660->rr_moved == NULL &&
		    file->name.s &&
		    (strcmp(file->name.s, "rr_moved") == 0 ||
		     strcmp(file->name.s, ".rr_moved") == 0)) {
			iso9660->rr_moved = file;
			file->rr_moved = 1;
			file->rr_moved_has_re_only = 1;
			file->re = 0;
			parent->subdirs--;
		} else if (file->re) {
			/*
			 * Sanity check: file's parent is rr_moved.
			 */
			if (parent == NULL || parent->rr_moved == 0) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Invalid Rockridge RE");
				goto fail;
			}
			/*
			 * Sanity check: file does not have "CL" extension.
			 */
			if (file->cl_offset) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Invalid Rockridge RE and CL");
				goto fail;
			}
			/*
			 * Sanity check: The file type must be a directory.
			 */
			if ((flags & 0x02) == 0) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Invalid Rockridge RE");
				goto fail;
			}
		} else if (parent != NULL && parent->rr_moved)
			file->rr_moved_has_re_only = 0;
		else if (parent != NULL && (flags & 0x02) &&
		    (parent->re || parent->re_descendant))
			file->re_descendant = 1;
		if (file->cl_offset) {
			struct file_info *r;

			if (parent == NULL || parent->parent == NULL) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Invalid Rockridge CL");
				goto fail;
			}
			/*
			 * Sanity check: The file type must be a regular file.
			 */
			if ((flags & 0x02) != 0) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Invalid Rockridge CL");
				goto fail;
			}
			parent->subdirs++;
			/* Overwrite an offset and a number of this "CL" entry
			 * to appear before other dirs. "+1" to those is to
			 * make sure to appear after "RE" entry which this
			 * "CL" entry should be connected with. */
			file->offset = file->number = file->cl_offset + 1;

			/*
			 * Sanity check: cl_offset does not point at its
			 * the parents or itself.
			 */
			for (r = parent; r; r = r->parent) {
				if (r->offset == file->cl_offset) {
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