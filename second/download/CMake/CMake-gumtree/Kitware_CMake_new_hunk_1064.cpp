seek_pack(struct archive_read *a)

{

	struct _7zip *zip = (struct _7zip *)a->format->data;

	int64_t pack_offset;



	if (zip->pack_stream_remaining <= 0) {

		archive_set_error(&(a->archive),

