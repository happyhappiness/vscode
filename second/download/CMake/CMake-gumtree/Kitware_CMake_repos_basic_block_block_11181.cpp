{
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