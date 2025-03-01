static int
zisofs_free(struct archive_write *a)
{
	struct iso9660 *iso9660 = a->format_data;
	int ret = ARCHIVE_OK;

	free(iso9660->zisofs.block_pointers);
	if (iso9660->zisofs.stream_valid &&
	    deflateEnd(&(iso9660->zisofs.stream)) != Z_OK) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Failed to clean up compressor");
		ret = ARCHIVE_FATAL;
	}
	iso9660->zisofs.block_pointers = NULL;
	iso9660->zisofs.stream_valid = 0;
	return (ret);
}