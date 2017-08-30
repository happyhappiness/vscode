		if (zip->pack_stream_inbytes_remaining == 0 &&
		    zip->folder_outbytes_remaining == 0)
			break;
		if (eof || (bytes_in == 0 && bytes_out == 0)) {
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC, "Damaged 7-Zip archive");
			return (ARCHIVE_FATAL);
