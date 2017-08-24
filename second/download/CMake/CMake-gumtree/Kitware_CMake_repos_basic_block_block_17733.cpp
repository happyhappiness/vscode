(zip->cctx_valid) {
				size_t outl = remainder;
				ret = archive_encrypto_aes_ctr_update(
				    &zip->cctx, zip->buf, remainder,
				    zip->buf, &outl);
				if (ret < 0) {
					archive_set_error(&a->archive,
					    ARCHIVE_ERRNO_MISC,
					    "Failed to encrypt file");
					return (ARCHIVE_FAILED);
				}
				archive_hmac_sha1_update(&zip->hctx,
				    zip->buf, remainder);
			}