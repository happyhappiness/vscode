					zip->len_buf);
				if (ret != ARCHIVE_OK)
					return (ret);
				zip->entry_compressed_written += zip->len_buf;
				zip->written_bytes += zip->len_buf;
				zip->stream.next_out = zip->buf;
				zip->stream.avail_out = (uInt)zip->len_buf;
			}
		} while (zip->stream.avail_in != 0);
		break;
#endif

	default:
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Invalid ZIP compression type");
		return ARCHIVE_FATAL;
	}

	zip->entry_uncompressed_limit -= s;
	zip->entry_crc32 = zip->crc32func(zip->entry_crc32, buff, (unsigned)s);
	return (s);

}

static int
archive_write_zip_finish_entry(struct archive_write *a)
{
	struct zip *zip = a->format_data;
	int ret;

#if HAVE_ZLIB_H
	if (zip->entry_compression == COMPRESSION_DEFLATE) {
		for (;;) {
			size_t remainder;
			ret = deflate(&zip->stream, Z_FINISH);
			if (ret == Z_STREAM_ERROR)
				return (ARCHIVE_FATAL);
			remainder = zip->len_buf - zip->stream.avail_out;
			ret = __archive_write_output(a, zip->buf, remainder);
			if (ret != ARCHIVE_OK)
				return (ret);
			zip->entry_compressed_written += remainder;
			zip->written_bytes += remainder;
			zip->stream.next_out = zip->buf;
			if (zip->stream.avail_out != 0)
				break;
			zip->stream.avail_out = (uInt)zip->len_buf;
		}
		deflateEnd(&zip->stream);
	}
#endif

	/* Write trailing data descriptor. */
	if ((zip->entry_flags & ZIP_ENTRY_FLAG_LENGTH_AT_END) != 0) {
		char d[24];
		memcpy(d, "PK\007\010", 4);
		archive_le32enc(d + 4, zip->entry_crc32);
		if (zip->entry_uses_zip64) {
			archive_le64enc(d + 8, (uint64_t)zip->entry_compressed_written);
			archive_le64enc(d + 16, (uint64_t)zip->entry_uncompressed_written);
			ret = __archive_write_output(a, d, 24);
			zip->written_bytes += 24;
		} else {
			archive_le32enc(d + 8, (uint32_t)zip->entry_compressed_written);
			archive_le32enc(d + 12, (uint32_t)zip->entry_uncompressed_written);
			ret = __archive_write_output(a, d, 16);
			zip->written_bytes += 16;
		}
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}

	/* Append Zip64 extra data to central directory information. */
	if (zip->entry_compressed_written > 0xffffffffLL
	    || zip->entry_uncompressed_written > 0xffffffffLL
	    || zip->entry_offset > 0xffffffffLL) {
		unsigned char zip64[32];
		unsigned char *z = zip64, *zd;
		memcpy(z, "\001\000\000\000", 4);
		z += 4;
		if (zip->entry_uncompressed_written >= 0xffffffffLL) {
			archive_le64enc(z, zip->entry_uncompressed_written);
			z += 8;
		}
		if (zip->entry_compressed_written >= 0xffffffffLL) {
			archive_le64enc(z, zip->entry_compressed_written);
			z += 8;
		}
		if (zip->entry_offset >= 0xffffffffLL) {
			archive_le64enc(z, zip->entry_offset);
			z += 8;
		}
		archive_le16enc(zip64 + 2, z - (zip64 + 4));
		zd = cd_alloc(zip, z - zip64);
		if (zd == NULL) {
			archive_set_error(&a->archive, ENOMEM,
				"Can't allocate zip data");
			return (ARCHIVE_FATAL);
		}
		memcpy(zd, zip64, z - zip64);
		/* Zip64 means version needs to be set to at least 4.5 */
		if (archive_le16dec(zip->file_header + 6) < 45)
			archive_le16enc(zip->file_header + 6, 45);
	}

	/* Fix up central directory file header. */
	archive_le32enc(zip->file_header + 16, zip->entry_crc32);
	archive_le32enc(zip->file_header + 20,
	    zipmin(zip->entry_compressed_written, 0xffffffffLL));
	archive_le32enc(zip->file_header + 24,
	    zipmin(zip->entry_uncompressed_written, 0xffffffffLL));
	archive_le16enc(zip->file_header + 30,
	    zip->central_directory_bytes - zip->file_header_extra_offset);
	archive_le32enc(zip->file_header + 42,
	    zipmin(zip->entry_offset, 0xffffffffLL));

	return (ARCHIVE_OK);
}

static int
archive_write_zip_close(struct archive_write *a)
{
	uint8_t buff[64];
	int64_t offset_start, offset_end;
	struct zip *zip = a->format_data;
	struct cd_segment *segment;
	int ret;

	offset_start = zip->written_bytes;
	segment = zip->central_directory;
	while (segment != NULL) {
		ret = __archive_write_output(a,
		    segment->buff, segment->p - segment->buff);
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
		zip->written_bytes += segment->p - segment->buff;
		segment = segment->next;
	}
	offset_end = zip->written_bytes;

	/* If central dir info is too large, write Zip64 end-of-cd */
	if (offset_end - offset_start > 0xffffffffLL
	    || offset_start > 0xffffffffLL
	    || zip->central_directory_entries > 0xffffUL
	    || (zip->flags & ZIP_FLAG_FORCE_ZIP64)) {
	  /* Zip64 end-of-cd record */
	  memset(buff, 0, 56);
	  memcpy(buff, "PK\006\006", 4);
	  archive_le64enc(buff + 4, 44);
	  archive_le16enc(buff + 12, 45);
	  archive_le16enc(buff + 14, 45);
	  /* This is disk 0 of 0. */
	  archive_le64enc(buff + 24, zip->central_directory_entries);
	  archive_le64enc(buff + 32, zip->central_directory_entries);
	  archive_le64enc(buff + 40, offset_end - offset_start);
	  archive_le64enc(buff + 48, offset_start);
	  ret = __archive_write_output(a, buff, 56);
	  if (ret != ARCHIVE_OK)
		  return (ARCHIVE_FATAL);
	  zip->written_bytes += 56;

	  /* Zip64 end-of-cd locator record. */
	  memset(buff, 0, 20);
	  memcpy(buff, "PK\006\007", 4);
	  archive_le32enc(buff + 4, 0);
	  archive_le64enc(buff + 8, offset_end);
	  archive_le32enc(buff + 16, 1);
	  ret = __archive_write_output(a, buff, 20);
	  if (ret != ARCHIVE_OK)
		  return (ARCHIVE_FATAL);
	  zip->written_bytes += 20;

	}

	/* Format and write end of central directory. */
	memset(buff, 0, sizeof(buff));
	memcpy(buff, "PK\005\006", 4);
	archive_le16enc(buff + 8, zipmin(0xffffU, zip->central_directory_entries));
	archive_le16enc(buff + 10, zipmin(0xffffU, zip->central_directory_entries));
	archive_le32enc(buff + 12, (uint32_t)zipmin(0xffffffffLL, (offset_end - offset_start)));
	archive_le32enc(buff + 16, (uint32_t)zipmin(0xffffffffLL, offset_start));
	ret = __archive_write_output(a, buff, 22);
	if (ret != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	zip->written_bytes += 22;
	return (ARCHIVE_OK);
}

static int
archive_write_zip_free(struct archive_write *a)
{
	struct zip *zip;
	struct cd_segment *segment;

	zip = a->format_data;
	while (zip->central_directory != NULL) {
		segment = zip->central_directory;
		zip->central_directory = segment->next;
		free(segment->buff);
		free(segment);
	}
#ifdef HAVE_ZLIB_H
	free(zip->buf);
#endif
	archive_entry_free(zip->entry);
	/* TODO: Free opt_sconv, sconv_default */

	free(zip);
	a->format_data = NULL;
	return (ARCHIVE_OK);
