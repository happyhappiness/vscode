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
	if (offset_end - offset_start > ZIP_4GB_MAX
	    || offset_start > ZIP_4GB_MAX
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
	archive_le16enc(buff + 8, (uint16_t)zipmin(0xffffU,
		zip->central_directory_entries));
	archive_le16enc(buff + 10, (uint16_t)zipmin(0xffffU,
		zip->central_directory_entries));
	archive_le32enc(buff + 12,
		(uint32_t)zipmin(ZIP_4GB_MAX, (offset_end - offset_start)));
	archive_le32enc(buff + 16,
		(uint32_t)zipmin(ZIP_4GB_MAX, offset_start));
	ret = __archive_write_output(a, buff, 22);
	if (ret != ARCHIVE_OK)
		return (ARCHIVE_FATAL);
	zip->written_bytes += 22;
	return (ARCHIVE_OK);
}