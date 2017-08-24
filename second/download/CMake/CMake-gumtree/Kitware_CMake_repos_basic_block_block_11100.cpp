{
		struct cffile *file = &(hd->file_array[i]);
		ssize_t avail;

		if ((p = __archive_read_ahead(a, 16, NULL)) == NULL)
			return (truncated_error(a));
		file->uncompressed_size = archive_le32dec(p + CFFILE_cbFile);
		file->offset = archive_le32dec(p + CFFILE_uoffFolderStart);
		file->folder = archive_le16dec(p + CFFILE_iFolder);
		file->mtime = cab_dos_time(p + CFFILE_date_time);
		file->attr = (uint8_t)archive_le16dec(p + CFFILE_attribs);
		__archive_read_consume(a, 16);

		cab->cab_offset += 16;
		if ((p = cab_read_ahead_remaining(a, 256, &avail)) == NULL)
			return (truncated_error(a));
		if ((len = cab_strnlen(p, avail-1)) <= 0)
			goto invalid;

		/* Copy a pathname.  */
		archive_string_init(&(file->pathname));
		archive_strncpy(&(file->pathname), p, len);
		__archive_read_consume(a, len + 1);
		cab->cab_offset += len + 1;

		/*
		 * Sanity check if each data is acceptable.
		 */
		if (file->uncompressed_size > 0x7FFF8000)
			goto invalid;/* Too large */
		if ((int64_t)file->offset + (int64_t)file->uncompressed_size
		    > ARCHIVE_LITERAL_LL(0x7FFF8000))
			goto invalid;/* Too large */
		switch (file->folder) {
		case iFoldCONTINUED_TO_NEXT:
			/* This must be last file in a folder. */
			if (i != hd->file_count -1)
				goto invalid;
			cur_folder = hd->folder_count -1;
			break;
		case iFoldCONTINUED_PREV_AND_NEXT:
			/* This must be only one file in a folder. */
			if (hd->file_count != 1)
				goto invalid;
			/* FALL THROUGH */
		case iFoldCONTINUED_FROM_PREV:
			/* This must be first file in a folder. */
			if (i != 0)
				goto invalid;
			prev_folder = cur_folder = 0;
			offset32 = file->offset;
			break;
		default:
			if (file->folder >= hd->folder_count)
				goto invalid;
			cur_folder = file->folder;
			break;
		}
		/* Dot not back track. */
		if (cur_folder < prev_folder)
			goto invalid;
		if (cur_folder != prev_folder)
			offset32 = 0;
		prev_folder = cur_folder;

		/* Make sure there are not any blanks from last file
		 * contents. */
		if (offset32 != file->offset)
			goto invalid;
		offset32 += file->uncompressed_size;

		/* CFDATA is available for file contents. */
		if (file->uncompressed_size > 0 &&
		    hd->folder_array[cur_folder].cfdata_count == 0)
			goto invalid;
	}