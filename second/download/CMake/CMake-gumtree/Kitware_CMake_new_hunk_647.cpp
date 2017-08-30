
	if (s == 0) return 0;

	if (zip->entry_flags & ZIP_ENTRY_FLAG_ENCRYPTED) {
		switch (zip->entry_encryption) {
		case ENCRYPTION_TRADITIONAL:
			/* Initialize traditoinal PKWARE encryption context. */
			if (!zip->tctx_valid) {
				ret = init_traditional_pkware_encryption(a);
				if (ret != ARCHIVE_OK)
					return (ret);
				zip->tctx_valid = 1;
			}
			break;
		case ENCRYPTION_WINZIP_AES128:
		case ENCRYPTION_WINZIP_AES256:
			if (!zip->cctx_valid) {
				ret = init_winzip_aes_encryption(a);
				if (ret != ARCHIVE_OK)
					return (ret);
				zip->cctx_valid = zip->hctx_valid = 1;
			}
			break;
		default:
			break;
		}
	}

	switch (zip->entry_compression) {
	case COMPRESSION_STORE:
		if (zip->tctx_valid || zip->cctx_valid) {
			const uint8_t *rb = (const uint8_t *)buff;
			const uint8_t * const re = rb + s;

			while (rb < re) {
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
		} else {
			ret = __archive_write_output(a, buff, s);
			if (ret != ARCHIVE_OK)
				return (ret);
			zip->written_bytes += s;
			zip->entry_compressed_written += s;
		}
		break;
#if HAVE_ZLIB_H
	case COMPRESSION_DEFLATE:
