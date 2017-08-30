#endif



static int

archive_read_format_zip_read_data(struct archive_read *a,

    const void **buff, size_t *size, int64_t *offset)

{

	int r;

	struct zip *zip = (struct zip *)(a->format->data);



	if (zip->has_encrypted_entries == ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {

		zip->has_encrypted_entries = 0;

	}



