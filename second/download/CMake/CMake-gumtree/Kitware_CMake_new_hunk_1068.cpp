			return (NULL);
		}
	}
	uavail = (uint16_t)cab->stream.total_out;

	if (uavail < cfdata->uncompressed_size) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
