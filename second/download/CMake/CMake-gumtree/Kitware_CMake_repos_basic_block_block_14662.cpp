{
		if (lzma_lzma_preset(&data->lzma_opt, data->compression_level)) {
			archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
			    "Internal error initializing compression library");
		}
		data->lzmafilters[0].id = LZMA_FILTER_LZMA2;
		data->lzmafilters[0].options = &data->lzma_opt;
		data->lzmafilters[1].id = LZMA_VLI_UNKNOWN;/* Terminate */
	}