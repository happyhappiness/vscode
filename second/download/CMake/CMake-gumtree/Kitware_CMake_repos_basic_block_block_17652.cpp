{
		archive_le32enc(local_header + 18, (uint32_t)zip->entry_compressed_size);
		archive_le32enc(local_header + 22, (uint32_t)zip->entry_uncompressed_size);
	}