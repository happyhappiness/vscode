 *	id1+size1+data1 + id2+size2+data2 ...
 *  triplets.  id and size are 2 bytes each.
 */
static int
process_extra(struct archive_read *a, const char *p, size_t extra_length, struct zip_entry* zip_entry)
{
	unsigned offset = 0;

	if (extra_length == 0) {
		return ARCHIVE_OK;
	}

	if (extra_length < 4) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Too-small extra data: Need at least 4 bytes, but only found %d bytes", (int)extra_length);
		return ARCHIVE_FAILED;
	}
	while (offset <= extra_length - 4) {
		unsigned short headerid = archive_le16dec(p + offset);
		unsigned short datasize = archive_le16dec(p + offset + 2);

		offset += 4;
		if (offset + datasize > extra_length) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
			    "Extra data overflow: Need %d bytes but only found %d bytes",
			    (int)datasize, (int)(extra_length - offset));
			return ARCHIVE_FAILED;
		}
#ifdef DEBUG
		fprintf(stderr, "Header id 0x%04x, length %d\n",
