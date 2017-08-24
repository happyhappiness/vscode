(block_count--) {
		data_pos = RSRC_H_SIZE + archive_le32dec(block_info++);
		data_size = archive_le32dec(block_info++);
		r = fgetxattr(a->fd, XATTR_RESOURCEFORK_NAME,
		    a->compressed_buffer, data_size, data_pos, 0);
		if (r != data_size)  {
			archive_set_error(&a->archive,
			    (r < 0)?errno:ARCHIVE_ERRNO_MISC,
			    "Failed to read resource fork");
			return (ARCHIVE_WARN);
		}
		if (a->compressed_buffer[0] == 0xff) {
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
		do {
			bytes_written = write(a->fd, b, bytes_to_write);
			if (bytes_written < 0) {
				archive_set_error(&a->archive, errno,
				    "Write failed");
				return (ARCHIVE_WARN);
			}
			bytes_to_write -= bytes_written;
			b += bytes_written;
		} while (bytes_to_write > 0);
	}