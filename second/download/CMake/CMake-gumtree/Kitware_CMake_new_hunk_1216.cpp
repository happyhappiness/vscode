}

static ssize_t
read_stream(struct archive_read *a, const void **buff, size_t size,
    size_t minimum)
{
	struct _7zip *zip = (struct _7zip *)a->format->data;
	uint64_t skip_bytes = 0;
	int r;

	if (zip->uncompressed_buffer_bytes_remaining == 0) {
		if (zip->pack_stream_inbytes_remaining > 0) {
			r = extract_pack_stream(a, 0);
			if (r < 0)
				return (r);
			return (get_uncompressed_data(a, buff, size, minimum));
		} else if (zip->folder_outbytes_remaining > 0) {
			/* Extract a remaining pack stream. */
			r = extract_pack_stream(a, 0);
			if (r < 0)
				return (r);
			return (get_uncompressed_data(a, buff, size, minimum));
		}
	} else
		return (get_uncompressed_data(a, buff, size, minimum));

	/*
	 * Current pack stream has been consumed.
	 */
	if (zip->pack_stream_remaining == 0) {
		if (zip->header_is_being_read) {
			/* Invalid sequence. This might happen when
			 * reading a malformed archive. */
			archive_set_error(&(a->archive),
			    ARCHIVE_ERRNO_MISC, "Malformed 7-Zip archive");
			return (ARCHIVE_FATAL);
		}

		/*
		 * All current folder's pack streams have been
		 * consumed. Switch to next folder.
		 */
		if (zip->folder_index == 0 &&
		    (zip->si.ci.folders[zip->entry->folderIndex].skipped_bytes
		     || zip->folder_index != zip->entry->folderIndex)) {
