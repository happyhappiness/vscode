(cab->entry_cffolder->cfdata_index <
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