			entries[i].flg |= MTIME_IS_SET;

			break;

		}

	}



	free(timeBools);

	return (0);

failed:

	free(timeBools);

	return (-1);

}



static int

decode_encoded_header_info(struct archive_read *a, struct _7z_stream_info *si)

{

	struct _7zip *zip = (struct _7zip *)a->format->data;



	errno = 0;

	if (read_StreamsInfo(a, si) < 0) {

		if (errno == ENOMEM)

			archive_set_error(&a->archive, -1,

			    "Couldn't allocate memory");

