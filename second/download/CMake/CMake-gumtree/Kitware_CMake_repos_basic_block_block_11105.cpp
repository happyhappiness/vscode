{
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