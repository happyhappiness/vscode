{
	struct _7zip *zip;
	unsigned char *wb;
	uint64_t header_offset, header_size, header_unpacksize;
	uint64_t length;
	uint32_t header_crc32;
	int r;

	zip = (struct _7zip *)a->format_data;

	if (zip->total_number_entry > 0) {
		struct archive_rb_node *n;
		uint64_t data_offset, data_size, data_unpacksize;
		unsigned header_compression;

		r = (int)compress_out(a, NULL, 0, ARCHIVE_Z_FINISH);
		if (r < 0)
			return (r);
		data_offset = 0;
		data_size = zip->stream.total_out;
		data_unpacksize = zip->stream.total_in;
		zip->coder.codec = zip->opt_compression;
		zip->coder.prop_size = zip->stream.prop_size;
		zip->coder.props = zip->stream.props;
		zip->stream.prop_size = 0;
		zip->stream.props = NULL;
		zip->total_number_nonempty_entry =
		    zip->total_number_entry - zip->total_number_empty_entry;

		/* Connect an empty file list. */
		if (zip->empty_list.first != NULL) {
			*zip->file_list.last = zip->empty_list.first;
			zip->file_list.last = zip->empty_list.last;
		}
		/* Connect a directory file list. */
		ARCHIVE_RB_TREE_FOREACH(n, &(zip->rbtree)) {
			file_register(zip, (struct file *)n);
		}

		/*
		 * NOTE: 7z command supports just LZMA1, LZMA2 and COPY for
		 * the compression type for encoding the header.
		 */
#if HAVE_LZMA_H
		header_compression = _7Z_LZMA1;
		/* If the stored file is only one, do not encode the header.
		 * This is the same way 7z command does. */
		if (zip->total_number_entry == 1)
			header_compression = _7Z_COPY;
#else
		header_compression = _7Z_COPY;
#endif
		r = _7z_compression_init_encoder(a, header_compression, 6);
		if (r < 0)
			return (r);
		zip->crc32flg = PRECODE_CRC32;
		zip->precode_crc32 = 0;
		r = make_header(a, data_offset, data_size, data_unpacksize,
			1, &(zip->coder));
		if (r < 0)
			return (r);
		r = (int)compress_out(a, NULL, 0, ARCHIVE_Z_FINISH);
		if (r < 0)
			return (r);
		header_offset = data_offset + data_size;
		header_size = zip->stream.total_out;
		header_crc32 = zip->precode_crc32;
		header_unpacksize = zip->stream.total_in;

		if (header_compression != _7Z_COPY) {
			/*
			 * Encode the header in order to reduce the size
			 * of the archive.
			 */
			free(zip->coder.props);
			zip->coder.codec = header_compression;
			zip->coder.prop_size = zip->stream.prop_size;
			zip->coder.props = zip->stream.props;
			zip->stream.prop_size = 0;
			zip->stream.props = NULL;

			r = _7z_compression_init_encoder(a, _7Z_COPY, 0);
			if (r < 0)
				return (r);
			zip->crc32flg = ENCODED_CRC32;
			zip->encoded_crc32 = 0;

			/*
			 * Make EncodedHeader.
			 */
			r = enc_uint64(a, kEncodedHeader);
			if (r < 0)
				return (r);
			r = make_streamsInfo(a, header_offset, header_size,
			      header_unpacksize, 1, &(zip->coder), 0,
			      header_crc32);
			if (r < 0)
				return (r);
			r = (int)compress_out(a, NULL, 0, ARCHIVE_Z_FINISH);
			if (r < 0)
				return (r);
			header_offset = header_offset + header_size;
			header_size = zip->stream.total_out;
			header_crc32 = zip->encoded_crc32;
		}
		zip->crc32flg = 0;
	} else {
		header_offset = header_size = 0;
		header_crc32 = 0;
	}
	
	length = zip->temp_offset;

	/*
	 * Make the zip header on wbuff(write buffer).
	 */
	wb = zip->wbuff;
	zip->wbuff_remaining = sizeof(zip->wbuff);
	memcpy(&wb[0], "7z\xBC\xAF\x27\x1C", 6);
	wb[6] = 0;/* Major version. */
	wb[7] = 3;/* Minor version. */
	archive_le64enc(&wb[12], header_offset);/* Next Header Offset */
	archive_le64enc(&wb[20], header_size);/* Next Header Size */
	archive_le32enc(&wb[28], header_crc32);/* Next Header CRC */
	archive_le32enc(&wb[8], crc32(0, &wb[12], 20));/* Start Header CRC */
	zip->wbuff_remaining -= 32;

	/*
	 * Read all file contents and an encoded header from the temporary
	 * file and write out it.
	 */
	r = copy_out(a, 0, length);
	if (r != ARCHIVE_OK)
		return (r);
	r = flush_wbuff(a);
	return (r);
}