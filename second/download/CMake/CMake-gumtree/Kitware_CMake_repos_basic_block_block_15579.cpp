(lastrm->avail_in == 0 && action == ARCHIVE_Z_FINISH) {
		__archive_ppmd7_functions.Ppmd7z_RangeEnc_FlushData(
			&(strm->range_enc));
		strm->stat = 1;
		/* Return EOF if there are no remaining bytes. */
		if (strm->buff_bytes == 0)
			return (ARCHIVE_EOF);
	}