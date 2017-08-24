(zip->hctx_valid) {
		uint8_t hmac[20];
		size_t hmac_len = 20;

		archive_hmac_sha1_final(&zip->hctx, hmac, &hmac_len);
		ret = __archive_write_output(a, hmac, AUTH_CODE_SIZE);
		if (ret != ARCHIVE_OK)
			return (ret);
		zip->entry_compressed_written += AUTH_CODE_SIZE;
		zip->written_bytes += AUTH_CODE_SIZE;
	}