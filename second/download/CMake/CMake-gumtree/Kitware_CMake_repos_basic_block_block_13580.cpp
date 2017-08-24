(zip->decrypted_bytes_remaining < (size_t)bytes_avail) {
			size_t buff_remaining =
			    (zip->decrypted_buffer + zip->decrypted_buffer_size)
			    - (zip->decrypted_ptr + zip->decrypted_bytes_remaining);

			if (buff_remaining > (size_t)bytes_avail)
				buff_remaining = (size_t)bytes_avail;

			if (0 == (zip->entry->zip_flags & ZIP_LENGTH_AT_END) &&
			      zip->entry_bytes_remaining > 0) {
				if ((int64_t)(zip->decrypted_bytes_remaining
				    + buff_remaining)
				      > zip->entry_bytes_remaining) {
					if (zip->entry_bytes_remaining <
					      (int64_t)zip->decrypted_bytes_remaining)
						buff_remaining = 0;
					else
						buff_remaining =
						    (size_t)zip->entry_bytes_remaining
						      - zip->decrypted_bytes_remaining;
				}
			}
			if (buff_remaining > 0) {
				if (zip->tctx_valid) {
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
				zip->decrypted_bytes_remaining += buff_remaining;
			}
		}