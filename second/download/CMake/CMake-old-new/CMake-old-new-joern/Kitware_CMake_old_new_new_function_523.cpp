static struct file_info *
parse_file_info(struct archive_read *a, struct file_info *parent,
    const unsigned char *isodirrec)
{
	struct iso9660 *iso9660;
	struct file_info *file, *filep;
	size_t name_len;
	const unsigned char *rr_start, *rr_end;
	const unsigned char *p;
	size_t dr_len;
	uint64_t fsize, offset;
	int32_t location;
	int flags;

	iso9660 = (struct iso9660 *)(a->format->data);

	dr_len = (size_t)isodirrec[DR_length_offset];
	name_len = (size_t)isodirrec[DR_name_len_offset];
	location = archive_le32dec(isodirrec + DR_extent_offset);
	fsize = toi(isodirrec + DR_size_offset, DR_size_size);
	/* Sanity check that dr_len needs at least 34. */
	if (dr_len < 34) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Invalid length of directory record");
		return (NULL);
	}
	/* Sanity check that name_len doesn't exceed dr_len. */
	if (dr_len - 33 < name_len || name_len == 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Invalid length of file identifier");
		return (NULL);
	}
	/* Sanity check that location doesn't exceed volume block.
	 * Don't check lower limit of location; it's possibility
	 * the location has negative value when file type is symbolic
	 * link or file size is zero. As far as I know latest mkisofs
	 * do that.
	 */
	if (location > 0 &&
	    (location + ((fsize + iso9660->logical_block_size -1)
	       / iso9660->logical_block_size))
			> (uint32_t)iso9660->volume_block) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Invalid location of extent of file");
		return (NULL);
	}
	/* Sanity check that location doesn't have a negative value
	 * when the file is not empty. it's too large. */
	if (fsize != 0 && location < 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Invalid location of extent of file");
		return (NULL);
	}

	/* Sanity check that this entry does not create a cycle. */
	offset = iso9660->logical_block_size * (uint64_t)location;
	for (filep = parent; filep != NULL; filep = filep->parent) {
		if (filep->offset == offset) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
			    "Directory structure contains loop");
			return (NULL);
		}
	}

	/* Create a new file entry and copy data from the ISO dir record. */
	file = (struct file_info *)calloc(1, sizeof(*file));
	if (file == NULL) {
		archive_set_error(&a->archive, ENOMEM,
		    "No memory for file entry");
		return (NULL);
	}
	file->parent = parent;
	file->offset = offset;
	file->size = fsize;
	file->mtime = isodate7(isodirrec + DR_date_offset);
	file->ctime = file->atime = file->mtime;
	file->rede_files.first = NULL;
	file->rede_files.last = &(file->rede_files.first);

	p = isodirrec + DR_name_offset;
	/* Rockridge extensions (if any) follow name.  Compute this
	 * before fidgeting the name_len below. */
	rr_start = p + name_len + (name_len & 1 ? 0 : 1);
	rr_end = isodirrec + dr_len;

	if (iso9660->seenJoliet) {
		/* Joliet names are max 64 chars (128 bytes) according to spec,
		 * but genisoimage/mkisofs allows recording longer Joliet
		 * names which are 103 UCS2 characters(206 bytes) by their
		 * option '-joliet-long'.
		 */
		if (name_len > 206)
			name_len = 206;
		name_len &= ~1;

		/* trim trailing first version and dot from filename.
		 *
		 * Remember we were in UTF-16BE land!
		 * SEPARATOR 1 (.) and SEPARATOR 2 (;) are both
		 * 16 bits big endian characters on Joliet.
		 *
		 * TODO: sanitize filename?
		 *       Joliet allows any UCS-2 char except:
		 *       *, /, :, ;, ? and \.
		 */
		/* Chop off trailing ';1' from files. */
		if (name_len > 4 && p[name_len-4] == 0 && p[name_len-3] == ';'
		    && p[name_len-2] == 0 && p[name_len-1] == '1')
			name_len -= 4;
#if 0 /* XXX: this somehow manages to strip of single-character file extensions, like '.c'. */
		/* Chop off trailing '.' from filenames. */
		if (name_len > 2 && p[name_len-2] == 0 && p[name_len-1] == '.')
			name_len -= 2;
#endif
		if ((file->utf16be_name = malloc(name_len)) == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "No memory for file name");
			return (NULL);
		}
		memcpy(file->utf16be_name, p, name_len);
		file->utf16be_bytes = name_len;
	} else {
		/* Chop off trailing ';1' from files. */
		if (name_len > 2 && p[name_len - 2] == ';' &&
				p[name_len - 1] == '1')
			name_len -= 2;
		/* Chop off trailing '.' from filenames. */
		if (name_len > 1 && p[name_len - 1] == '.')
			--name_len;

		archive_strncpy(&file->name, (const char *)p, name_len);
	}

	flags = isodirrec[DR_flags_offset];
	if (flags & 0x02)
		file->mode = AE_IFDIR | 0700;
	else
		file->mode = AE_IFREG | 0400;
	if (flags & 0x80)
		file->multi_extent = 1;
	else
		file->multi_extent = 0;
	/*
	 * Use a location for the file number, which is treated as an inode
	 * number to find out hardlink target. If Rockridge extensions is
	 * being used, the file number will be overwritten by FILE SERIAL
	 * NUMBER of RRIP "PX" extension.
	 * Note: Old mkisofs did not record that FILE SERIAL NUMBER
	 * in ISO images.
	 * Note2: xorriso set 0 to the location of a symlink file. 
	 */
	if (file->size == 0 && location >= 0) {
		/* If file->size is zero, its location points wrong place,
		 * and so we should not use it for the file number.
		 * When the location has negative value, it can be used
		 * for the file number.
		 */
		file->number = -1;
		/* Do not appear before any directory entries. */
		file->offset = -1;
	} else
		file->number = (int64_t)(uint32_t)location;

	/* Rockridge extensions overwrite information from above. */
	if (iso9660->opt_support_rockridge) {
		if (parent == NULL && rr_end - rr_start >= 7) {
			p = rr_start;
			if (memcmp(p, "SP\x07\x01\xbe\xef", 6) == 0) {
				/*
				 * SP extension stores the suspOffset
				 * (Number of bytes to skip between
				 * filename and SUSP records.)
				 * It is mandatory by the SUSP standard
				 * (IEEE 1281).
				 *
				 * It allows SUSP to coexist with
				 * non-SUSP uses of the System
				 * Use Area by placing non-SUSP data
				 * before SUSP data.
				 *
				 * SP extension must be in the root
				 * directory entry, disable all SUSP
				 * processing if not found.
				 */
				iso9660->suspOffset = p[6];
				iso9660->seenSUSP = 1;
				rr_start += 7;
			}
		}
		if (iso9660->seenSUSP) {
			int r;

			file->name_continues = 0;
			file->symlink_continues = 0;
			rr_start += iso9660->suspOffset;
			r = parse_rockridge(a, file, rr_start, rr_end);
			if (r != ARCHIVE_OK) {
				free(file);
				return (NULL);
			}
			/*
			 * A file size of symbolic link files in ISO images
			 * made by makefs is not zero and its location is
			 * the same as those of next regular file. That is
			 * the same as hard like file and it causes unexpected
			 * error. 
			 */
			if (file->size > 0 &&
			    (file->mode & AE_IFMT) == AE_IFLNK) {
				file->size = 0;
				file->number = -1;
				file->offset = -1;
			}
		} else
			/* If there isn't SUSP, disable parsing
			 * rock ridge extensions. */
			iso9660->opt_support_rockridge = 0;
	}

	file->nlinks = 1;/* Reset nlink. we'll calculate it later. */
	/* Tell file's parent how many children that parent has. */
	if (parent != NULL && (flags & 0x02))
		parent->subdirs++;

	if (iso9660->seenRockridge) {
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
				return (NULL);
			}
			/*
			 * Sanity check: file does not have "CL" extension.
			 */
			if (file->cl_offset) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Invalid Rockridge RE and CL");
				return (NULL);
			}
			/*
			 * Sanity check: The file type must be a directory.
			 */
			if ((flags & 0x02) == 0) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Invalid Rockridge RE");
				return (NULL);
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
				return (NULL);
			}
			/*
			 * Sanity check: The file type must be a regular file.
			 */
			if ((flags & 0x02) != 0) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Invalid Rockridge CL");
				return (NULL);
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
					return (NULL);
				}
			}
			if (file->cl_offset == file->offset ||
			    parent->rr_moved) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Invalid Rockridge CL");
				return (NULL);
			}
		}
	}

#if DEBUG
	/* DEBUGGING: Warn about attributes I don't yet fully support. */
	if ((flags & ~0x02) != 0) {
		fprintf(stderr, "\n ** Unrecognized flag: ");
		dump_isodirrec(stderr, isodirrec);
		fprintf(stderr, "\n");
	} else if (toi(isodirrec + DR_volume_sequence_number_offset, 2) != 1) {
		fprintf(stderr, "\n ** Unrecognized sequence number: ");
		dump_isodirrec(stderr, isodirrec);
		fprintf(stderr, "\n");
	} else if (*(isodirrec + DR_file_unit_size_offset) != 0) {
		fprintf(stderr, "\n ** Unexpected file unit size: ");
		dump_isodirrec(stderr, isodirrec);
		fprintf(stderr, "\n");
	} else if (*(isodirrec + DR_interleave_offset) != 0) {
		fprintf(stderr, "\n ** Unexpected interleave: ");
		dump_isodirrec(stderr, isodirrec);
		fprintf(stderr, "\n");
	} else if (*(isodirrec + DR_ext_attr_length_offset) != 0) {
		fprintf(stderr, "\n ** Unexpected extended attribute length: ");
		dump_isodirrec(stderr, isodirrec);
		fprintf(stderr, "\n");
	}
#endif
	register_file(iso9660, file);
	return (file);
}