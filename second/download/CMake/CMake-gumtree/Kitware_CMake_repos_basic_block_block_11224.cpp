{
		cab->uncompressed_buffer_size = 0x8000;
		cab->uncompressed_buffer
		    = (unsigned char *)malloc(cab->uncompressed_buffer_size);
		if (cab->uncompressed_buffer == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "No memory for CAB reader");
			*avail = ARCHIVE_FATAL;
			return (NULL);
		}
	}