static int
zisofs_write_to_temp(struct archive_write *a, const void *buff, size_t s)
{
	struct iso9660 *iso9660 = a->format_data;
	struct isofile *file = iso9660->cur_file;
	const unsigned char *b;
	z_stream *zstrm;
	size_t avail, csize;
	int flush, r;

	zstrm = &(iso9660->zisofs.stream);
	zstrm->next_out = wb_buffptr(a);
	zstrm->avail_out = (uInt)wb_remaining(a);
	b = (const unsigned char *)buff;
	do {
		avail = ZF_BLOCK_SIZE - zstrm->total_in;
		if (s < avail) {
			avail = s;
			flush = Z_NO_FLUSH;
		} else
			flush = Z_FINISH;
		iso9660->zisofs.remaining -= avail;
		if (iso9660->zisofs.remaining <= 0)
			flush = Z_FINISH;

		zstrm->next_in = (Bytef *)(uintptr_t)(const void *)b;
		zstrm->avail_in = (uInt)avail;

		/*
		 * Check if current data block are all zero.
		 */
		if (iso9660->zisofs.allzero) {
			const unsigned char *nonzero = b;
			const unsigned char *nonzeroend = b + avail;

			while (nonzero < nonzeroend)
				if (*nonzero++) {
					iso9660->zisofs.allzero = 0;
					break;
				}
		}
		b += avail;
		s -= avail;

		/*
		 * If current data block are all zero, we do not use
		 * compressed data.
		 */
		if (flush == Z_FINISH && iso9660->zisofs.allzero &&
		    avail + zstrm->total_in == ZF_BLOCK_SIZE) {
			if (iso9660->zisofs.block_offset !=
			    file->cur_content->size) {
				int64_t diff;

				r = wb_set_offset(a,
				    file->cur_content->offset_of_temp +
				        iso9660->zisofs.block_offset);
				if (r != ARCHIVE_OK)
					return (r);
				diff = file->cur_content->size -
				    iso9660->zisofs.block_offset;
				file->cur_content->size -= diff;
				iso9660->zisofs.total_size -= diff;
			}
			zstrm->avail_in = 0;
		}

		/*
		 * Compress file data.
		 */
		while (zstrm->avail_in > 0) {
			csize = zstrm->total_out;
			r = deflate(zstrm, flush);
			switch (r) {
			case Z_OK:
			case Z_STREAM_END:
				csize = zstrm->total_out - csize;
				if (wb_consume(a, csize) != ARCHIVE_OK)
					return (ARCHIVE_FATAL);
				iso9660->zisofs.total_size += csize;
				iso9660->cur_file->cur_content->size += csize;
				zstrm->next_out = wb_buffptr(a);
				zstrm->avail_out = (uInt)wb_remaining(a);
				break;
			default:
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Compression failed:"
				    " deflate() call returned status %d",
				    r);
				return (ARCHIVE_FATAL);
			}
		}

		if (flush == Z_FINISH) {
			/*
			 * Save the information of one zisofs block.
			 */
			iso9660->zisofs.block_pointers_idx ++;
			archive_le32enc(&(iso9660->zisofs.block_pointers[
			    iso9660->zisofs.block_pointers_idx]),
				(uint32_t)iso9660->zisofs.total_size);
			r = zisofs_init_zstream(a);
			if (r != ARCHIVE_OK)
				return (ARCHIVE_FATAL);
			iso9660->zisofs.allzero = 1;
			iso9660->zisofs.block_offset = file->cur_content->size;
		}
	} while (s);

	return (ARCHIVE_OK);
}