static int
archive_read_format_zip_read_data(struct archive_read *a,
    const void **buff, size_t *size, int64_t *offset)
{
	int r;
	struct zip *zip = (struct zip *)(a->format->data);

	*offset = zip->entry_uncompressed_bytes_read;
	*size = 0;
	*buff = NULL;

	/* If we hit end-of-entry last time, return ARCHIVE_EOF. */
	if (zip->end_of_entry)
		return (ARCHIVE_EOF);

	/* Return EOF immediately if this is a non-regular file. */
	if (AE_IFREG != (zip->entry->mode & AE_IFMT))
		return (ARCHIVE_EOF);

	if (zip->entry->flags & (ZIP_ENCRYPTED | ZIP_STRONG_ENCRYPTED)) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Encrypted file is unsupported");
		return (ARCHIVE_FAILED);
	}

	zip_read_consume(a, zip->unconsumed);
	zip->unconsumed = 0;

	switch(zip->entry->compression) {
	case 0:  /* No compression. */
		r =  zip_read_data_none(a, buff, size, offset);
		break;
#ifdef HAVE_ZLIB_H
	case 8: /* Deflate compression. */
		r =  zip_read_data_deflate(a, buff, size, offset);
		break;
#endif
	default: /* Unsupported compression. */
		/* Return a warning. */
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unsupported ZIP compression method (%s)",
		    compression_name(zip->entry->compression));
		/* We can't decompress this entry, but we will
		 * be able to skip() it and try the next entry. */
		return (ARCHIVE_FAILED);
		break;
	}
	if (r != ARCHIVE_OK)
		return (r);
	/* Update checksum */
	if (*size)
		zip->entry_crc32 = crc32(zip->entry_crc32, *buff,
		    (unsigned)*size);
	/* If we hit the end, swallow any end-of-data marker. */
	if (zip->end_of_entry) {
		/* Check file size, CRC against these values. */
		if (zip->entry->compressed_size !=
		    zip->entry_compressed_bytes_read) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "ZIP compressed data is wrong size "
			    "(read %jd, expected %jd)",
			    (intmax_t)zip->entry_compressed_bytes_read,
			    (intmax_t)zip->entry->compressed_size);
			return (ARCHIVE_WARN);
		}
		/* Size field only stores the lower 32 bits of the actual
		 * size. */
		if ((zip->entry->uncompressed_size & UINT32_MAX)
		    != (zip->entry_uncompressed_bytes_read & UINT32_MAX)) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "ZIP uncompressed data is wrong size "
			    "(read %jd, expected %jd)",
			    (intmax_t)zip->entry_uncompressed_bytes_read,
			    (intmax_t)zip->entry->uncompressed_size);
			return (ARCHIVE_WARN);
		}
		/* Check computed CRC against header */
		if (zip->entry->crc32 != zip->entry_crc32) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "ZIP bad CRC: 0x%lx should be 0x%lx",
			    (unsigned long)zip->entry_crc32,
			    (unsigned long)zip->entry->crc32);
			return (ARCHIVE_WARN);
		}
	}

	return (ARCHIVE_OK);
}