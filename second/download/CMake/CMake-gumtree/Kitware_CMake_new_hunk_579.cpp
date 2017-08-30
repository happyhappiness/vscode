#endif

static int
read_decryption_header(struct archive_read *a)
{
	struct zip *zip = (struct zip *)(a->format->data);
	const char *p;
	unsigned int remaining_size;
	unsigned int ts;

	/*
	 * Read an initialization vector data field.
	 */
	p = __archive_read_ahead(a, 2, NULL);
	if (p == NULL)
		goto truncated;
	ts = zip->iv_size;
	zip->iv_size = archive_le16dec(p);
	__archive_read_consume(a, 2);
	if (ts < zip->iv_size) {
		free(zip->iv);
		zip->iv = NULL;
	}
	p = __archive_read_ahead(a, zip->iv_size, NULL);
	if (p == NULL)
		goto truncated;
	if (zip->iv == NULL) {
		zip->iv = malloc(zip->iv_size);
		if (zip->iv == NULL)
			goto nomem;
	}
	memcpy(zip->iv, p, zip->iv_size);
	__archive_read_consume(a, zip->iv_size);

	/*
	 * Read a size of remaining decryption header field.
	 */
	p = __archive_read_ahead(a, 14, NULL);
	if (p == NULL)
		goto truncated;
	remaining_size = archive_le32dec(p);
	if (remaining_size < 16 || remaining_size > (1 << 18))
		goto corrupted;

	/* Check if format version is supported. */
	if (archive_le16dec(p+4) != 3) {
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unsupported encryption format version: %u",
		    archive_le16dec(p+4));
		return (ARCHIVE_FAILED);
	}

	/*
	 * Read an encryption algorithm field.
	 */
	zip->alg_id = archive_le16dec(p+6);
	switch (zip->alg_id) {
	case 0x6601:/* DES */
	case 0x6602:/* RC2 */
	case 0x6603:/* 3DES 168 */
	case 0x6609:/* 3DES 112 */
	case 0x660E:/* AES 128 */
	case 0x660F:/* AES 192 */
	case 0x6610:/* AES 256 */
	case 0x6702:/* RC2 (version >= 5.2) */
	case 0x6720:/* Blowfish */
	case 0x6721:/* Twofish */
	case 0x6801:/* RC4 */
		/* Suuported encryption algorithm. */
		break;
	default:
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unknown encryption algorithm: %u", zip->alg_id);
		return (ARCHIVE_FAILED);
	}

	/*
	 * Read a bit length field.
	 */
	zip->bit_len = archive_le16dec(p+8);

	/*
	 * Read a flags field.
	 */
	zip->flags = archive_le16dec(p+10);
	switch (zip->flags & 0xf000) {
	case 0x0001: /* Password is required to decrypt. */
	case 0x0002: /* Certificates only. */
	case 0x0003: /* Password or certificate required to decrypt. */
		break;
	default:
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unknown encryption flag: %u", zip->flags);
		return (ARCHIVE_FAILED);
	}
	if ((zip->flags & 0xf000) == 0 ||
	    (zip->flags & 0xf000) == 0x4000) {
		archive_set_error(&a->archive,
		    ARCHIVE_ERRNO_FILE_FORMAT,
		    "Unknown encryption flag: %u", zip->flags);
		return (ARCHIVE_FAILED);
	}

	/*
	 * Read an encrypted random data field.
	 */
	ts = zip->erd_size;
	zip->erd_size = archive_le16dec(p+12);
	__archive_read_consume(a, 14);
	if ((zip->erd_size & 0xf) != 0 ||
	    (zip->erd_size + 16) > remaining_size ||
	    (zip->erd_size + 16) < zip->erd_size)
		goto corrupted;

	if (ts < zip->erd_size) {
		free(zip->erd);
		zip->erd = NULL;
	}
	p = __archive_read_ahead(a, zip->erd_size, NULL);
	if (p == NULL)
		goto truncated;
	if (zip->erd == NULL) {
		zip->erd = malloc(zip->erd_size);
		if (zip->erd == NULL)
			goto nomem;
	}
	memcpy(zip->erd, p, zip->erd_size);
	__archive_read_consume(a, zip->erd_size);

	/*
	 * Read a reserved data field.
	 */
	p = __archive_read_ahead(a, 4, NULL);
	if (p == NULL)
		goto truncated;
	/* Reserved data size should be zero. */
	if (archive_le32dec(p) != 0)
		goto corrupted;
	__archive_read_consume(a, 4);

	/*
	 * Read a password validation data field.
	 */
	p = __archive_read_ahead(a, 2, NULL);
	if (p == NULL)
		goto truncated;
	ts = zip->v_size;
	zip->v_size = archive_le16dec(p);
	__archive_read_consume(a, 2);
	if ((zip->v_size & 0x0f) != 0 ||
	    (zip->erd_size + zip->v_size + 16) > remaining_size ||
	    (zip->erd_size + zip->v_size + 16) < (zip->erd_size + zip->v_size))
		goto corrupted;
	if (ts < zip->v_size) {
		free(zip->v_data);
		zip->v_data = NULL;
	}
	p = __archive_read_ahead(a, zip->v_size, NULL);
	if (p == NULL)
		goto truncated;
	if (zip->v_data == NULL) {
		zip->v_data = malloc(zip->v_size);
		if (zip->v_data == NULL)
			goto nomem;
	}
	memcpy(zip->v_data, p, zip->v_size);
	__archive_read_consume(a, zip->v_size);

	p = __archive_read_ahead(a, 4, NULL);
	if (p == NULL)
		goto truncated;
	zip->v_crc32 = archive_le32dec(p);
	__archive_read_consume(a, 4);

	/*return (ARCHIVE_OK);
	 * This is not fully implemnted yet.*/
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Encrypted file is unsupported");
	return (ARCHIVE_FAILED);
truncated:
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Truncated ZIP file data");
	return (ARCHIVE_FATAL);
corrupted:
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Corrupted ZIP file data");
	return (ARCHIVE_FATAL);
nomem:
	archive_set_error(&a->archive, ENOMEM,
	    "No memory for ZIP decryption");
	return (ARCHIVE_FATAL);
}

static int
zip_alloc_decryption_buffer(struct archive_read *a)
{
	struct zip *zip = (struct zip *)(a->format->data);
	size_t bs = 256 * 1024;

	if (zip->decrypted_buffer == NULL) {
		zip->decrypted_buffer_size = bs;
		zip->decrypted_buffer = malloc(bs);
		if (zip->decrypted_buffer == NULL) {
			archive_set_error(&a->archive, ENOMEM,
			    "No memory for ZIP decryption");
			return (ARCHIVE_FATAL);
		}
	}
	zip->decrypted_ptr = zip->decrypted_buffer;
	return (ARCHIVE_OK);
}

static int
init_traditional_PKWARE_decryption(struct archive_read *a)
{
	struct zip *zip = (struct zip *)(a->format->data);
	const void *p;
	int retry;
	int r;

	if (zip->tctx_valid)
		return (ARCHIVE_OK);

	/*
	   Read the 12 bytes encryption header stored at
	   the start of the data area.
	 */
#define ENC_HEADER_SIZE	12
	if (0 == (zip->entry->zip_flags & ZIP_LENGTH_AT_END)
	    && zip->entry_bytes_remaining < ENC_HEADER_SIZE) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated Zip encrypted body: only %jd bytes available",
		    (intmax_t)zip->entry_bytes_remaining);
		return (ARCHIVE_FATAL);
	}

	p = __archive_read_ahead(a, ENC_HEADER_SIZE, NULL);
	if (p == NULL) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
		    "Truncated ZIP file data");
		return (ARCHIVE_FATAL);
	}

	for (retry = 0;; retry++) {
		const char *passphrase;
		uint8_t crcchk;

		passphrase = __archive_read_next_passphrase(a);
		if (passphrase == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    (retry > 0)?
				"Incorrect passphrase":
				"Passphrase required for this entry");
			return (ARCHIVE_FAILED);
		}

		/*
		 * Initialize ctx for Traditional PKWARE Decyption.
		 */
		r = trad_enc_init(&zip->tctx, passphrase, strlen(passphrase),
			p, ENC_HEADER_SIZE, &crcchk);
		if (r == 0 && crcchk == zip->entry->decdat)
			break;/* The passphrase is OK. */
		if (retry > 10000) {
			/* Avoid infinity loop. */
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Too many incorrect passphrases");
			return (ARCHIVE_FAILED);
		}
	}

	__archive_read_consume(a, ENC_HEADER_SIZE);
	zip->tctx_valid = 1;
	if (0 == (zip->entry->zip_flags & ZIP_LENGTH_AT_END)) {
	    zip->entry_bytes_remaining -= ENC_HEADER_SIZE;
	}
	/*zip->entry_uncompressed_bytes_read += ENC_HEADER_SIZE;*/
	zip->entry_compressed_bytes_read += ENC_HEADER_SIZE;
	zip->decrypted_bytes_remaining = 0;

	return (zip_alloc_decryption_buffer(a));
#undef ENC_HEADER_SIZE
}

static int
init_WinZip_AES_decryption(struct archive_read *a)
{
	struct zip *zip = (struct zip *)(a->format->data);
	const void *p;
	const uint8_t *pv;
	size_t key_len, salt_len;
	uint8_t derived_key[MAX_DERIVED_KEY_BUF_SIZE];
	int retry;
	int r;

	if (zip->cctx_valid || zip->hctx_valid)
		return (ARCHIVE_OK);

	switch (zip->entry->aes_extra.strength) {
	case 1: salt_len = 8;  key_len = 16; break;
	case 2: salt_len = 12; key_len = 24; break;
	case 3: salt_len = 16; key_len = 32; break;
	default: goto corrupted;
	}
	p = __archive_read_ahead(a, salt_len + 2, NULL);
	if (p == NULL)
		goto truncated;

	for (retry = 0;; retry++) {
		const char *passphrase;

		passphrase = __archive_read_next_passphrase(a);
		if (passphrase == NULL) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    (retry > 0)?
				"Incorrect passphrase":
				"Passphrase required for this entry");
			return (ARCHIVE_FAILED);
		}
		memset(derived_key, 0, sizeof(derived_key));
		r = archive_pbkdf2_sha1(passphrase, strlen(passphrase),
		    p, salt_len, 1000, derived_key, key_len * 2 + 2);
		if (r != 0) {
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Decryption is unsupported due to lack of "
			    "crypto library");
			return (ARCHIVE_FAILED);
		}

		/* Check password verification value. */
		pv = ((const uint8_t *)p) + salt_len;
		if (derived_key[key_len * 2] == pv[0] &&
		    derived_key[key_len * 2 + 1] == pv[1])
			break;/* The passphrase is OK. */
		if (retry > 10000) {
			/* Avoid infinity loop. */
			archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
			    "Too many incorrect passphrases");
			return (ARCHIVE_FAILED);
		}
	}

	r = archive_decrypto_aes_ctr_init(&zip->cctx, derived_key, key_len);
	if (r != 0) {
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Decryption is unsupported due to lack of crypto library");
		return (ARCHIVE_FAILED);
	}
	r = archive_hmac_sha1_init(&zip->hctx, derived_key + key_len, key_len);
	if (r != 0) {
		archive_decrypto_aes_ctr_release(&zip->cctx);
		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,
		    "Failed to initialize HMAC-SHA1");
		return (ARCHIVE_FAILED);
	}
	zip->cctx_valid = zip->hctx_valid = 1;
	__archive_read_consume(a, salt_len + 2);
	zip->entry_bytes_remaining -= salt_len + 2 + AUTH_CODE_SIZE;
	if (0 == (zip->entry->zip_flags & ZIP_LENGTH_AT_END)
	    && zip->entry_bytes_remaining < 0)
		goto corrupted;
	zip->entry_compressed_bytes_read += salt_len + 2 + AUTH_CODE_SIZE;
	zip->decrypted_bytes_remaining = 0;

	zip->entry->compression = zip->entry->aes_extra.compression;
	return (zip_alloc_decryption_buffer(a));

truncated:
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Truncated ZIP file data");
	return (ARCHIVE_FATAL);
corrupted:
	archive_set_error(&a->archive, ARCHIVE_ERRNO_FILE_FORMAT,
	    "Corrupted ZIP file data");
	return (ARCHIVE_FATAL);
}

static int
archive_read_format_zip_read_data(struct archive_read *a,
    const void **buff, size_t *size, int64_t *offset)
{
	int r;
	struct zip *zip = (struct zip *)(a->format->data);

	if (zip->has_encrypted_entries ==
			ARCHIVE_READ_FORMAT_ENCRYPTION_DONT_KNOW) {
		zip->has_encrypted_entries = 0;
	}

