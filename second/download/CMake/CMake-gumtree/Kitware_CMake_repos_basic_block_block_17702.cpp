{
				size_t l;

				if (zip->tctx_valid) {
					l = trad_enc_encrypt_update(&zip->tctx,
					    rb, re - rb,
					    zip->buf, zip->len_buf);
				} else {
					l = zip->len_buf;
					ret = archive_encrypto_aes_ctr_update(
					    &zip->cctx,
					    rb, re - rb, zip->buf, &l);
					if (ret < 0) {
						archive_set_error(&a->archive,
						    ARCHIVE_ERRNO_MISC,
						    "Failed to encrypt file");
						return (ARCHIVE_FAILED);
					}
					archive_hmac_sha1_update(&zip->hctx,
					    zip->buf, l);
				}
				ret = __archive_write_output(a, zip->buf, l);
				if (ret != ARCHIVE_OK)
					return (ret);
				zip->entry_compressed_written += l;
				zip->written_bytes += l;
				rb += l;
			}