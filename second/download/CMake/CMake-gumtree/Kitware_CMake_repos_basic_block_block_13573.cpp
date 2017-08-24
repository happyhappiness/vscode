{
					size_t dsize = buff_remaining;
					archive_decrypto_aes_ctr_update(
					    &zip->cctx,
					    compressed_buff, buff_remaining,
					    zip->decrypted_ptr
					      + zip->decrypted_bytes_remaining,
					    &dsize);
				}