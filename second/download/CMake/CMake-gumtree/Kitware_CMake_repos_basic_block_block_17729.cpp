{
			size_t remainder;

			ret = deflate(&zip->stream, Z_FINISH);
			if (ret == Z_STREAM_ERROR)
				return (ARCHIVE_FATAL);
			remainder = zip->len_buf - zip->stream.avail_out;
			if (zip->tctx_valid) {
				trad_enc_encrypt_update(&zip->tctx,
				    zip->buf, remainder, zip->buf, remainder);
			} else if (zip->cctx_valid) {
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
			ret = __archive_write_output(a, zip->buf, remainder);
			if (ret != ARCHIVE_OK)
				return (ret);
			zip->entry_compressed_written += remainder;
			zip->written_bytes += remainder;
			zip->stream.next_out = zip->buf;
			if (zip->stream.avail_out != 0)
				break;
			zip->stream.avail_out = (uInt)zip->len_buf;
		}