		uint64_t flush_bytes;

		if (!zip->ppmd7_valid || zip->ppmd7_stat < 0 ||
		    t_avail_out <= 0) {
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC,
			    "Decompression internal error");
