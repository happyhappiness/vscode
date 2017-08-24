do {
			ret = deflate(&zip->stream, Z_NO_FLUSH);
			if (ret == Z_STREAM_ERROR)
				return (ARCHIVE_FATAL);
			if (zip->stream.avail_out == 0) {
				if (zip->tctx_valid) {
					trad_enc_encrypt_update(&zip->tctx,
					    zip->buf, zip->len_buf,
					    zip->buf, zip->len_buf);
				} else if (zip->cctx_valid) {
					size_t outl = zip->len_buf;
					ret = archive_encrypto_aes_ctr_update(
					    &zip->cctx,
					    zip->buf, zip->len_buf,
					    zip->buf, &outl);
					if (ret < 0) {
						archive_set_error(&a->archive,
						    ARCHIVE_ERRNO_MISC,
						    "Failed to encrypt file");
						return (ARCHIVE_FAILED);
					}
					archive_hmac_sha1_update(&zip->hctx,
					    zip->buf, zip->len_buf);
				}
				ret = __archive_write_output(a, zip->buf,
					zip->len_buf);
				if (ret != ARCHIVE_OK)
					return (ret);
				zip->entry_compressed_written += zip->len_buf;
				zip->written_bytes += zip->len_buf;
				zip->stream.next_out = zip->buf;
				zip->stream.avail_out = (uInt)zip->len_buf;
			}
		} while (zip->stream.avail_in != 0);