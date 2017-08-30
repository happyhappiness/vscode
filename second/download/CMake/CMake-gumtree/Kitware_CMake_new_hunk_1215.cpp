		}

		read_consume(a);

	}

	if (zip->uncompressed_buffer_bytes_remaining < minimum) {

		archive_set_error(&(a->archive),

		    ARCHIVE_ERRNO_MISC, "Damaged 7-Zip archive");

		return (ARCHIVE_FATAL);

	}

	zip->uncompressed_buffer_pointer = zip->uncompressed_buffer;

	return (ARCHIVE_OK);

}

