((lha->setflag & CRC_IS_SET) &&
		    lha->crc != lha->entry_crc_calculated) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "LHa data CRC error");
			r = ARCHIVE_WARN;
		}