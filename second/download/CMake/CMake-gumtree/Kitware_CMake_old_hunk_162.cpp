 *	id1+size1+data1 + id2+size2+data2 ...
 *  triplets.  id and size are 2 bytes each.
 */
static void
process_extra(const char *p, size_t extra_length, struct zip_entry* zip_entry)
{
	unsigned offset = 0;

	while (offset < extra_length - 4) {
		unsigned short headerid = archive_le16dec(p + offset);
		unsigned short datasize = archive_le16dec(p + offset + 2);

		offset += 4;
		if (offset + datasize > extra_length) {
			break;
		}
#ifdef DEBUG
		fprintf(stderr, "Header id 0x%04x, length %d\n",
