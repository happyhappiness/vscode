{
			trad_enc_decrypt_update(&zip->tctx,
			    (const uint8_t *)buff, dec_size,
			    zip->decrypted_buffer, dec_size);
		}