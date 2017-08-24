(zip->tctx_valid) {
					trad_enc_decrypt_update(&zip->tctx,
					    compressed_buff, buff_remaining,
					    zip->decrypted_ptr
					      + zip->decrypted_bytes_remaining,
					    buff_remaining);
				} else {
					size_t dsize = buff_remaining;
					archive_decrypto_aes_ctr_update(
					    &zip->cctx,
					    compressed_buff, buff_remaining,
					    zip->decrypted_ptr
					      + zip->decrypted_bytes_remaining,
					    &dsize);
				}