{
	struct cab *cab = (struct cab *)(a->format->data);
	struct cfdata *cfdata = cab->entry_cfdata;

	/* There are remaining bytes in current CFDATA, use it first. */
	if (cfdata != NULL && cfdata->uncompressed_bytes_remaining > 0)
		return (ARCHIVE_OK);

	if (cfdata == NULL) {
		int64_t skip;

		cab->entry_cffolder->cfdata_index = 0;

		/* Seek read pointer to the offset of CFDATA if needed. */
		skip = cab->entry_cffolder->cfdata_offset_in_cab
			- cab->cab_offset;
		if (skip < 0) {
			int folder_index;
			switch (cab->entry_cffile->folder) {
			case iFoldCONTINUED_FROM_PREV:
			case iFoldCONTINUED_PREV_AND_NEXT:
				folder_index = 0;
				break;
			case iFoldCONTINUED_TO_NEXT:
				folder_index = cab->cfheader.folder_count-1;
				break;
			default:
				folder_index = cab->entry_cffile->folder;
				break;
			}
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Invalid offset of CFDATA in folder(%d) %jd < %jd",
			    folder_index,
			    (intmax_t)cab->entry_cffolder->cfdata_offset_in_cab,
			    (intmax_t)cab->cab_offset);
			return (ARCHIVE_FATAL);
		}
		if (skip > 0) {
			if (__archive_read_consume(a, skip) < 0)
				return (ARCHIVE_FATAL);
			cab->cab_offset =
			    cab->entry_cffolder->cfdata_offset_in_cab;
		}
	}

	/*
	 * Read a CFDATA.
	 */
	if (cab->entry_cffolder->cfdata_index <
	    cab->entry_cffolder->cfdata_count) {
		const unsigned char *p;
		int l;

		cfdata = &(cab->entry_cffolder->cfdata);
		cab->entry_cffolder->cfdata_index++;
		cab->entry_cfdata = cfdata;
		cfdata->sum_calculated = 0;
		cfdata->sum_extra_avail = 0;
		cfdata->sum_ptr = NULL;
		l = 8;
		if (cab->cfheader.flags & RESERVE_PRESENT)
			l += cab->cfheader.cfdata;
		if ((p = __archive_read_ahead(a, l, NULL)) == NULL)
			return (truncated_error(a));
		cfdata->sum = archive_le32dec(p + CFDATA_csum);
		cfdata->compressed_size = archive_le16dec(p + CFDATA_cbData);
		cfdata->compressed_bytes_remaining = cfdata->compressed_size;
		cfdata->uncompressed_size =
		    archive_le16dec(p + CFDATA_cbUncomp);
		cfdata->uncompressed_bytes_remaining =
		    cfdata->uncompressed_size;
		cfdata->uncompressed_avail = 0;
		cfdata->read_offset = 0;
		cfdata->unconsumed = 0;

		/*
		 * Sanity check if data size is acceptable.
		 */
		if (cfdata->compressed_size == 0 ||
		    cfdata->compressed_size > (0x8000+6144))
			goto invalid;
		if (cfdata->uncompressed_size > 0x8000)
			goto invalid;
		if (cfdata->uncompressed_size == 0) {
			switch (cab->entry_cffile->folder) {
			case iFoldCONTINUED_PREV_AND_NEXT:
			case iFoldCONTINUED_TO_NEXT:
				break;
			case iFoldCONTINUED_FROM_PREV:
			default:
				goto invalid;
			}
		}
		/* If CFDATA is not last in a folder, an uncompressed
		 * size must be 0x8000(32KBi) */
		if ((cab->entry_cffolder->cfdata_index <
		     cab->entry_cffolder->cfdata_count) &&
		       cfdata->uncompressed_size != 0x8000)
			goto invalid;

		/* A compressed data size and an uncompressed data size must
		 * be the same in no compression mode. */
		if (cab->entry_cffolder->comptype == COMPTYPE_NONE &&
		    cfdata->compressed_size != cfdata->uncompressed_size)
			goto invalid;

		/*
		 * Save CFDATA image for sum check.
		 */
		if (cfdata->memimage_size < (size_t)l) {
			free(cfdata->memimage);
			cfdata->memimage = malloc(l);
			if (cfdata->memimage == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "Can't allocate memory for CAB data");
				return (ARCHIVE_FATAL);
			}
			cfdata->memimage_size = l;
		}
		memcpy(cfdata->memimage, p, l);

		/* Consume bytes as much as we used. */
		__archive_read_consume(a, l);
		cab->cab_offset += l;
	} else if (cab->entry_cffolder->cfdata_count > 0) {
		/* Run out of all CFDATA in a folder. */
		cfdata->compressed_size = 0;
		cfdata->uncompressed_size = 0;
		cfdata->compressed_bytes_remaining = 0;
		cfdata->uncompressed_bytes_remaining = 0;
	} else {
		/* Current folder does not have any CFDATA. */
		cfdata = &(cab->entry_cffolder->cfdata);
		cab->entry_cfdata = cfdata;
		memset(cfdata, 0, sizeof(*cfdata));
	}
	return (ARCHIVE_OK);
invalid:
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Invalid CFDATA");
	return (ARCHIVE_FATAL);
}