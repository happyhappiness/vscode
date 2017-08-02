archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Checksum error CFDATA[%d] %x:%x in %d bytes",
		    cab->entry_cffolder->cfdata_index -1,
		    cfdata->sum, cfdata->sum_calculated,
		    cfdata->compressed_size)