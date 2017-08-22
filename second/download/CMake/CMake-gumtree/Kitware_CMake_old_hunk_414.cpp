		lha->entry_unconsumed = 0;
	}
	if (lha->end_of_entry) {
		if (!lha->end_of_entry_cleanup) {
			if ((lha->setflag & CRC_IS_SET) &&
			    lha->crc != lha->entry_crc_calculated) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "LHa data CRC error");
				return (ARCHIVE_WARN);
			}

			/* End-of-entry cleanup done. */
			lha->end_of_entry_cleanup = 1;
		}
		*offset = lha->entry_offset;
		*size = 0;
		*buff = NULL;
		return (ARCHIVE_EOF);
	}

	if (lha->entry_is_compressed)
