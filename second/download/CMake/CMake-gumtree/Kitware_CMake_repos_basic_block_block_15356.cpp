{
		ssize_t bytes;
		const void *p = (const void *)archive_entry_symlink(entry);
		bytes = compress_out(a, p, (size_t)file->size, ARCHIVE_Z_RUN);
		if (bytes < 0)
			return ((int)bytes);
		zip->entry_crc32 = crc32(zip->entry_crc32, p, (unsigned)bytes);
		zip->entry_bytes_remaining -= bytes;
	}