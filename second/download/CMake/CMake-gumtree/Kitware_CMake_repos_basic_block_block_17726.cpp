{
		char d[24];
		memcpy(d, "PK\007\010", 4);
		if (zip->cctx_valid && zip->aes_vendor == AES_VENDOR_AE_2)
			archive_le32enc(d + 4, 0);/* no CRC.*/
		else
			archive_le32enc(d + 4, zip->entry_crc32);
		if (zip->entry_uses_zip64) {
			archive_le64enc(d + 8,
				(uint64_t)zip->entry_compressed_written);
			archive_le64enc(d + 16,
				(uint64_t)zip->entry_uncompressed_written);
			ret = __archive_write_output(a, d, 24);
			zip->written_bytes += 24;
		} else {
			archive_le32enc(d + 8,
				(uint32_t)zip->entry_compressed_written);
			archive_le32enc(d + 12,
				(uint32_t)zip->entry_uncompressed_written);
			ret = __archive_write_output(a, d, 16);
			zip->written_bytes += 16;
		}
		if (ret != ARCHIVE_OK)
			return (ARCHIVE_FATAL);
	}