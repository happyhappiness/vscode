}



int

archive_read_set_callback_data(struct archive *_a, void *client_data)

{

	struct archive_read *a = (struct archive_read *)_a;

	archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,

	    "archive_read_set_callback_data");

	a->client.data = client_data;

	return ARCHIVE_OK;

}



int

archive_read_open1(struct archive *_a)

{

	struct archive_read *a = (struct archive_read *)_a;

	struct archive_read_filter *filter;

	int slot, e;



	archive_check_magic(_a, ARCHIVE_READ_MAGIC, ARCHIVE_STATE_NEW,

	    "archive_read_open");

