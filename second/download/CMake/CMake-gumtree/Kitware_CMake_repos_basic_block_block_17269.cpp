(strict && copy_length < V7TAR_name_size)
		memcpy(h + V7TAR_name_offset, pp, copy_length);
	else if (!strict && copy_length <= V7TAR_name_size)
		memcpy(h + V7TAR_name_offset, pp, copy_length);
	else {
		/* Prefix is too long. */
		archive_set_error(&a->archive, ENAMETOOLONG,
		    "Pathname too long");
		ret = ARCHIVE_FAILED;
	}