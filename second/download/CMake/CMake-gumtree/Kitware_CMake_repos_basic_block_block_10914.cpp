(zip->uncompressed_buffer_size < minimum) {
			/*
			 * Expand the uncompressed buffer up to
			 * the minimum size.
			 */
			void *p;
			size_t new_size;

			new_size = minimum + 1023;
			new_size &= ~0x3ff;
			p = realloc(zip->uncompressed_buffer, new_size);
			if (p == NULL) {
				archive_set_error(&a->archive, ENOMEM,
				    "No memory for 7-Zip decompression");
				return (ARCHIVE_FATAL);
			}
			zip->uncompressed_buffer = (unsigned char *)p;
			zip->uncompressed_buffer_size = new_size;
		}