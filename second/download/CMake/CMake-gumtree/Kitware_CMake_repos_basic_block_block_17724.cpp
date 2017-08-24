{
			archive_le32enc(d + 8,
				(uint32_t)zip->entry_compressed_written);
			archive_le32enc(d + 12,
				(uint32_t)zip->entry_uncompressed_written);
			ret = __archive_write_output(a, d, 16);
			zip->written_bytes += 16;
		}