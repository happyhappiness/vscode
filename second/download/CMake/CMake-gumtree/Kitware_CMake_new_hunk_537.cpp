	struct private_data *data = (struct private_data *)f->data;



	if (strcmp(key, "compression-level") == 0) {

		int val;

		if (value == NULL || !((val = value[0] - '0') >= 1 && val <= 9) ||

		    value[1] != '\0')

			return (ARCHIVE_WARN);



#ifndef HAVE_LZ4HC_H

		if(val >= 3)

		{

			archive_set_error(f->archive, ARCHIVE_ERRNO_PROGRAMMER,

				"High compression not included in this build");

			return (ARCHIVE_FATAL);

		}

#endif

		data->compression_level = val;

		return (ARCHIVE_OK);

	}

	if (strcmp(key, "stream-checksum") == 0) {

