			 * Expand the uncompressed buffer up to
			 * the minimum size.
			 */
			zip->uncompressed_buffer_size = minimum + 1023;
			zip->uncompressed_buffer_size &= ~0x3ff;
			zip->uncompressed_buffer =
			    realloc(zip->uncompressed_buffer,
				zip->uncompressed_buffer_size);
			if (zip->uncompressed_buffer == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "No memory for 7-Zip decompression");
				return (ARCHIVE_FATAL);
			}
		}
		/*
		 * Move unconsumed bytes to the head.
