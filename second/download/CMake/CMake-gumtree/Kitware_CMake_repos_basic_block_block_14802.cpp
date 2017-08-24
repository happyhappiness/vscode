(a->compressed_buffer[0] == 0xff) {
			bytes_to_write = data_size -1;
			b = a->compressed_buffer + 1;
		} else {
			uLong dest_len = MAX_DECMPFS_BLOCK_SIZE;
			int zr;

			zr = uncompress((Bytef *)a->uncompressed_buffer,
			    &dest_len, a->compressed_buffer, data_size);
			if (zr != Z_OK) {
				archive_set_error(&a->archive,
				    ARCHIVE_ERRNO_MISC,
				    "Failed to decompress resource fork");
				return (ARCHIVE_WARN);
			}
			bytes_to_write = dest_len;
			b = (unsigned char *)a->uncompressed_buffer;
		}