{	/* ARCHIVE_FILTER_LZIP */
		int dict_size = data->lzma_opt.dict_size;
		int ds, log2dic, wedges;

		/* Calculate a coded dictionary size */
		if (dict_size < (1 << 12) || dict_size > (1 << 27)) {
			archive_set_error(f->archive, ARCHIVE_ERRNO_MISC,
			    "Unacceptable dictionary size for lzip: %d",
			    dict_size);
			return (ARCHIVE_FATAL);
		}
		for (log2dic = 27; log2dic >= 12; log2dic--) {
			if (dict_size & (1 << log2dic))
				break;
		}
		if (dict_size > (1 << log2dic)) {
			log2dic++;
			wedges =
			    ((1 << log2dic) - dict_size) / (1 << (log2dic - 4));
		} else
			wedges = 0;
		ds = ((wedges << 5) & 0xe0) | (log2dic & 0x1f);

		data->crc32 = 0;
		/* Make a header */
		data->compressed[0] = 0x4C;
		data->compressed[1] = 0x5A;
		data->compressed[2] = 0x49;
		data->compressed[3] = 0x50;
		data->compressed[4] = 1;/* Version */
		data->compressed[5] = (unsigned char)ds;
		data->stream.next_out += 6;
		data->stream.avail_out -= 6;

		ret = lzma_raw_encoder(&(data->stream), data->lzmafilters);
	}