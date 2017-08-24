{
				if (skip > (int64_t)sizeof(nullblock))
					bytes_written = hfs_write_decmpfs_block(
					    a, nullblock, sizeof(nullblock));
				else
					bytes_written = hfs_write_decmpfs_block(
					    a, nullblock, skip);
				if (bytes_written < 0) {
					archive_set_error(&a->archive, errno,
					    "Write failed");
					return (ARCHIVE_WARN);
				}
				skip -= bytes_written;
			}