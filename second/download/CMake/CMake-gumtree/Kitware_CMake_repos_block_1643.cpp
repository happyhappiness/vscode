{
	const unsigned char *p;
	struct cab *cab;
	struct cfheader *hd;
	size_t bytes, used;
	ssize_t len;
	int64_t skip;
	int err, i;
	int cur_folder, prev_folder;
	uint32_t offset32;
	
	a->archive.archive_format = ARCHIVE_FORMAT_CAB;
	if (a->archive.archive_format_name == NULL)
		a->archive.archive_format_name = "CAB";

	if ((p = __archive_read_ahead(a, 42, NULL)) == NULL)
		return (truncated_error(a));

	cab = (struct cab *)(a->format->data);
	if (cab->found_header == 0 &&
	    p[0] == 'M' && p[1] == 'Z') {
		/* This is an executable?  Must be self-extracting... */
		err = cab_skip_sfx(a);
		if (err < ARCHIVE_WARN)
			return (err);

		/* Re-read header after processing the SFX. */
		if ((p = __archive_read_ahead(a, 42, NULL)) == NULL)
			return (truncated_error(a));
	}

	cab->cab_offset = 0;
	/*
	 * Read CFHEADER.
	 */
	hd = &cab->cfheader;
	if (p[CFHEADER_signature+0] != 'M' || p[CFHEADER_signature+1] != 'S' ||
	    p[CFHEADER_signature+2] != 'C' || p[CFHEADER_signature+3] != 'F') {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Couldn't find out CAB header");
		return (ARCHIVE_FATAL);
	}
	hd->total_bytes = archive_le32dec(p + CFHEADER_cbCabinet);
	hd->files_offset = archive_le32dec(p + CFHEADER_coffFiles);
	hd->minor = p[CFHEADER_versionMinor];
	hd->major = p[CFHEADER_versionMajor];
	hd->folder_count = archive_le16dec(p + CFHEADER_cFolders);
	if (hd->folder_count == 0)
		goto invalid;
	hd->file_count = archive_le16dec(p + CFHEADER_cFiles);
	if (hd->file_count == 0)
		goto invalid;
	hd->flags = archive_le16dec(p + CFHEADER_flags);
	hd->setid = archive_le16dec(p + CFHEADER_setID);
	hd->cabinet = archive_le16dec(p + CFHEADER_iCabinet);
	used = CFHEADER_iCabinet + 2;
	if (hd->flags & RESERVE_PRESENT) {
		uint16_t cfheader;
		cfheader = archive_le16dec(p + CFHEADER_cbCFHeader);
		if (cfheader > 60000U)
			goto invalid;
		hd->cffolder = p[CFHEADER_cbCFFolder];
		hd->cfdata = p[CFHEADER_cbCFData];
		used += 4;/* cbCFHeader, cbCFFolder and cbCFData */
		used += cfheader;/* abReserve */
	} else
		hd->cffolder = 0;/* Avoid compiling warning. */
	if (hd->flags & PREV_CABINET) {
		/* How many bytes are used for szCabinetPrev. */
		if ((p = __archive_read_ahead(a, used+256, NULL)) == NULL)
			return (truncated_error(a));
		if ((len = cab_strnlen(p + used, 255)) <= 0)
			goto invalid;
		used += len + 1;
		/* How many bytes are used for szDiskPrev. */
		if ((p = __archive_read_ahead(a, used+256, NULL)) == NULL)
			return (truncated_error(a));
		if ((len = cab_strnlen(p + used, 255)) <= 0)
			goto invalid;
		used += len + 1;
	}
	if (hd->flags & NEXT_CABINET) {
		/* How many bytes are used for szCabinetNext. */
		if ((p = __archive_read_ahead(a, used+256, NULL)) == NULL)
			return (truncated_error(a));
		if ((len = cab_strnlen(p + used, 255)) <= 0)
			goto invalid;
		used += len + 1;
		/* How many bytes are used for szDiskNext. */
		if ((p = __archive_read_ahead(a, used+256, NULL)) == NULL)
			return (truncated_error(a));
		if ((len = cab_strnlen(p + used, 255)) <= 0)
			goto invalid;
		used += len + 1;
	}
	__archive_read_consume(a, used);
	cab->cab_offset += used;
	used = 0;

	/*
	 * Read CFFOLDER.
	 */
	hd->folder_array = (struct cffolder *)calloc(
	    hd->folder_count, sizeof(struct cffolder));
	if (hd->folder_array == NULL)
		goto nomem;
	
	bytes = 8;
	if (hd->flags & RESERVE_PRESENT)
		bytes += hd->cffolder;
	bytes *= hd->folder_count;
	if ((p = __archive_read_ahead(a, bytes, NULL)) == NULL)
		return (truncated_error(a));
	offset32 = 0;
	for (i = 0; i < hd->folder_count; i++) {
		struct cffolder *folder = &(hd->folder_array[i]);
		folder->cfdata_offset_in_cab =
		    archive_le32dec(p + CFFOLDER_coffCabStart);
		folder->cfdata_count = archive_le16dec(p+CFFOLDER_cCFData);
		folder->comptype =
		    archive_le16dec(p+CFFOLDER_typeCompress) & 0x0F;
		folder->compdata =
		    archive_le16dec(p+CFFOLDER_typeCompress) >> 8;
		/* Get a compression name. */
		if (folder->comptype <
		    sizeof(compression_name) / sizeof(compression_name[0]))
			folder->compname = compression_name[folder->comptype];
		else
			folder->compname = "UNKNOWN";
		p += 8;
		used += 8;
		if (hd->flags & RESERVE_PRESENT) {
			p += hd->cffolder;/* abReserve */
			used += hd->cffolder;
		}
		/*
		 * Sanity check if each data is acceptable.
		 */
		if (offset32 >= folder->cfdata_offset_in_cab)
			goto invalid;
		offset32 = folder->cfdata_offset_in_cab;

		/* Set a request to initialize zlib for the CFDATA of
		 * this folder. */
		folder->decompress_init = 0;
	}
	__archive_read_consume(a, used);
	cab->cab_offset += used;

	/*
	 * Read CFFILE.
	 */
	/* Seek read pointer to the offset of CFFILE if needed. */
	skip = (int64_t)hd->files_offset - cab->cab_offset;
	if (skip <  0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Invalid offset of CFFILE %jd < %jd",
		    (intmax_t)hd->files_offset, (intmax_t)cab->cab_offset);
		return (ARCHIVE_FATAL);
	}
	if (skip) {
		__archive_read_consume(a, skip);
		cab->cab_offset += skip;
	}
	/* Allocate memory for CFDATA */
	hd->file_array = (struct cffile *)calloc(
	    hd->file_count, sizeof(struct cffile));
	if (hd->file_array == NULL)
		goto nomem;

	prev_folder = -1;
	for (i = 0; i < hd->file_count; i++) {
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

	if (hd->cabinet != 0 || hd->flags & (PREV_CABINET | NEXT_CABINET)) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Multivolume cabinet file is unsupported");
		return (ARCHIVE_WARN);
	}
	return (ARCHIVE_OK);
invalid:
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Invalid CAB header");
	return (ARCHIVE_FATAL);
nomem:
	archive_set_error(&a->archive, ENOMEM,
	    "Can't allocate memory for CAB data");
	return (ARCHIVE_FATAL);
}