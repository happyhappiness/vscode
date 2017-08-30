	struct private_data *data = (struct private_data *)f->data;



	if (strcmp(key, "compression-level") == 0) {

		if (value == NULL || !(value[0] >= '1' && value[0] <= '9') ||

		    value[1] != '\0')

			return (ARCHIVE_WARN);

		data->compression_level = value[0] - '0';

		return (ARCHIVE_OK);

	}

	if (strcmp(key, "stream-checksum") == 0) {

