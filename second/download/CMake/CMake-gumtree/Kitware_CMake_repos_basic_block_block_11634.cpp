{
	struct iso9660 *iso9660;
	struct file_info *file;
	int r, rd_r = ARCHIVE_OK;

	iso9660 = (struct iso9660 *)(a->format->data);

	if (!a->archive.archive_format) {
		a->archive.archive_format = ARCHIVE_FORMAT_ISO9660;
		a->archive.archive_format_name = "ISO9660";
	}

	if (iso9660->current_position == 0) {
		r = choose_volume(a, iso9660);
		if (r != ARCHIVE_OK)
			return (r);
	}

	file = NULL;/* Eliminate a warning. */
	/* Get the next entry that appears after the current offset. */
	r = next_entry_seek(a, iso9660, &file);
	if (r != ARCHIVE_OK)
		return (r);

	if (iso9660->seenJoliet) {
		/*
		 * Convert UTF-16BE of a filename to local locale MBS
		 * and store the result into a filename field.
		 */
		if (iso9660->sconv_utf16be == NULL) {
			iso9660->sconv_utf16be =
			    archive_string_conversion_from_charset(
				&(a->archive), "UTF-16BE", 1);
			if (iso9660->sconv_utf16be == NULL)
				/* Couldn't allocate memory */
				return (ARCHIVE_FATAL);
		}
		if (iso9660->utf16be_path == NULL) {
			iso9660->utf16be_path = malloc(UTF16_NAME_MAX);
			if (iso9660->utf16be_path == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "No memory");
				return (ARCHIVE_FATAL);
			}
		}
		if (iso9660->utf16be_previous_path == NULL) {
			iso9660->utf16be_previous_path = malloc(UTF16_NAME_MAX);
			if (iso9660->utf16be_previous_path == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "No memory");
				return (ARCHIVE_FATAL);
			}
		}

		iso9660->utf16be_path_len = 0;
		if (build_pathname_utf16be(iso9660->utf16be_path,
		    UTF16_NAME_MAX, &(iso9660->utf16be_path_len), file) != 0) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Pathname is too long");
			return (ARCHIVE_FATAL);
		}

		r = archive_entry_copy_pathname_l(entry,
		    (const char *)iso9660->utf16be_path,
		    iso9660->utf16be_path_len,
		    iso9660->sconv_utf16be);
		if (r != 0) {
			if (errno == ENOMEM) {
				archive_set_error(&a->archive, ENOMEM,
				    "No memory for Pathname");
				return (ARCHIVE_FATAL);
			}
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Pathname cannot be converted "
			    "from %s to current locale.",
			    archive_string_conversion_charset_name(
			      iso9660->sconv_utf16be));

			rd_r = ARCHIVE_WARN;
		}
	} else {
		const char *path = build_pathname(&iso9660->pathname, file, 0);
		if (path == NULL) {
			archive_set_error(&a->archive,
			    ARCHIVE_ERRNO_FILE_FORMAT,
			    "Pathname is too long");
			return (ARCHIVE_FATAL);
		} else {
			archive_string_empty(&iso9660->pathname);
			archive_entry_set_pathname(entry, path);
		}
	}

	iso9660->entry_bytes_remaining = file->size;
	/* Offset for sparse-file-aware clients. */
	iso9660->entry_sparse_offset = 0;

	if (file->offset + file->size > iso9660->volume_size) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "File is beyond end-of-media: %s",
		    archive_entry_pathname(entry));
		iso9660->entry_bytes_remaining = 0;
		return (ARCHIVE_WARN);
	}

	/* Set up the entry structure with information about this entry. */
	archive_entry_set_mode(entry, file->mode);
	archive_entry_set_uid(entry, file->uid);
	archive_entry_set_gid(entry, file->gid);
	archive_entry_set_nlink(entry, file->nlinks);
	if (file->birthtime_is_set)
		archive_entry_set_birthtime(entry, file->birthtime, 0);
	else
		archive_entry_unset_birthtime(entry);
	archive_entry_set_mtime(entry, file->mtime, 0);
	archive_entry_set_ctime(entry, file->ctime, 0);
	archive_entry_set_atime(entry, file->atime, 0);
	/* N.B.: Rock Ridge supports 64-bit device numbers. */
	archive_entry_set_rdev(entry, (dev_t)file->rdev);
	archive_entry_set_size(entry, iso9660->entry_bytes_remaining);
	if (file->symlink.s != NULL)
		archive_entry_copy_symlink(entry, file->symlink.s);

	/* Note: If the input isn't seekable, we can't rewind to
	 * return the same body again, so if the next entry refers to
	 * the same data, we have to return it as a hardlink to the
	 * original entry. */
	if (file->number != -1 &&
	    file->number == iso9660->previous_number) {
		if (iso9660->seenJoliet) {
			r = archive_entry_copy_hardlink_l(entry,
			    (const char *)iso9660->utf16be_previous_path,
			    iso9660->utf16be_previous_path_len,
			    iso9660->sconv_utf16be);
			if (r != 0) {
				if (errno == ENOMEM) {
					archive_set_error(&a->archive, ENOMEM,
					    "No memory for Linkname");
					return (ARCHIVE_FATAL);
				}
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_FILE_FORMAT,
				    "Linkname cannot be converted "
				    "from %s to current locale.",
				    archive_string_conversion_charset_name(
				      iso9660->sconv_utf16be));
				rd_r = ARCHIVE_WARN;
			}
		} else
			archive_entry_set_hardlink(entry,
			    iso9660->previous_pathname.s);
		archive_entry_unset_size(entry);
		iso9660->entry_bytes_remaining = 0;
		return (rd_r);
	}

	if ((file->mode & AE_IFMT) != AE_IFDIR &&
	    file->offset < iso9660->current_position) {
		int64_t r64;

		r64 = __archive_read_seek(a, file->offset, SEEK_SET);
		if (r64 != (int64_t)file->offset) {
			/* We can't seek backwards to extract it, so issue
			 * a warning.  Note that this can only happen if
			 * this entry was added to the heap after we passed
			 * this offset, that is, only if the directory
			 * mentioning this entry is later than the body of
			 * the entry. Such layouts are very unusual; most
			 * ISO9660 writers lay out and record all directory
			 * information first, then store all file bodies. */
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Ignoring out-of-order file @%jx (%s) %jd < %jd",
			    (intmax_t)file->number,
			    iso9660->pathname.s,
			    (intmax_t)file->offset,
			    (intmax_t)iso9660->current_position);
			iso9660->entry_bytes_remaining = 0;
			return (ARCHIVE_WARN);
		}
		iso9660->current_position = (uint64_t)r64;
	}

	/* Initialize zisofs variables. */
	iso9660->entry_zisofs.pz = file->pz;
	if (file->pz) {
#ifdef HAVE_ZLIB_H
		struct zisofs  *zisofs;

		zisofs = &iso9660->entry_zisofs;
		zisofs->initialized = 0;
		zisofs->pz_log2_bs = file->pz_log2_bs;
		zisofs->pz_uncompressed_size = file->pz_uncompressed_size;
		zisofs->pz_offset = 0;
		zisofs->header_avail = 0;
		zisofs->header_passed = 0;
		zisofs->block_pointers_avail = 0;
#endif
		archive_entry_set_size(entry, file->pz_uncompressed_size);
	}

	iso9660->previous_number = file->number;
	if (iso9660->seenJoliet) {
		memcpy(iso9660->utf16be_previous_path, iso9660->utf16be_path,
		    iso9660->utf16be_path_len);
		iso9660->utf16be_previous_path_len = iso9660->utf16be_path_len;
	} else
		archive_strcpy(
		    &iso9660->previous_pathname, iso9660->pathname.s);

	/* Reset entry_bytes_remaining if the file is multi extent. */
	iso9660->entry_content = file->contents.first;
	if (iso9660->entry_content != NULL)
		iso9660->entry_bytes_remaining = iso9660->entry_content->size;

	if (archive_entry_filetype(entry) == AE_IFDIR) {
		/* Overwrite nlinks by proper link number which is
		 * calculated from number of sub directories. */
		archive_entry_set_nlink(entry, 2 + file->subdirs);
		/* Directory data has been read completely. */
		iso9660->entry_bytes_remaining = 0;
	}

	if (rd_r != ARCHIVE_OK)
		return (rd_r);
	return (ARCHIVE_OK);
}