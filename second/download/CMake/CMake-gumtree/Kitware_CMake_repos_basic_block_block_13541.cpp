(zip->tctx_valid || zip->cctx_valid) {
		size_t dec_size = bytes_avail;

		if (dec_size > zip->decrypted_buffer_size)
			dec_size = zip->decrypted_buffer_size;
		if (zip->tctx_valid) {
			trad_enc_decrypt_update(&zip->tctx,
			    (const uint8_t *)buff, dec_size,
			    zip->decrypted_buffer, dec_size);
		} else {
			size_t dsize = dec_size;
			archive_hmac_sha1_update(&zip->hctx,
			    (const uint8_t *)buff, dec_size);
			archive_decrypto_aes_ctr_update(&zip->cctx,
			    (const uint8_t *)buff, dec_size,
			    zip->decrypted_buffer, &dsize);
		}
		bytes_avail = dec_size;
		buff = (const char *)zip->decrypted_buffer;
	}