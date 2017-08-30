	}

	return (zip->sconv_default);

}



/*

  Traditional PKWARE Decryption functions.

 */



static void

trad_enc_update_keys(struct trad_enc_ctx *ctx, uint8_t c)

{

	uint8_t t;

#define CRC32(c, b) (crc32(c ^ 0xffffffffUL, &b, 1) ^ 0xffffffffUL)



	ctx->keys[0] = CRC32(ctx->keys[0], c);

	ctx->keys[1] = (ctx->keys[1] + (ctx->keys[0] & 0xff)) * 134775813L + 1;

	t = (ctx->keys[1] >> 24) & 0xff;

	ctx->keys[2] = CRC32(ctx->keys[2], t);

#undef CRC32

}



static uint8_t

trad_enc_decypt_byte(struct trad_enc_ctx *ctx)

{

	unsigned temp = ctx->keys[2] | 2;

	return (uint8_t)((temp * (temp ^ 1)) >> 8) & 0xff;

}



static unsigned

trad_enc_encrypt_update(struct trad_enc_ctx *ctx, const uint8_t *in,

    size_t in_len, uint8_t *out, size_t out_len)

{

	unsigned i, max;



	max = (unsigned)((in_len < out_len)? in_len: out_len);



	for (i = 0; i < max; i++) {

		uint8_t t = in[i];

		out[i] = t ^ trad_enc_decypt_byte(ctx);

		trad_enc_update_keys(ctx, t);

	}

	return i;

}



static int

trad_enc_init(struct trad_enc_ctx *ctx, const char *pw, size_t pw_len)

{



	ctx->keys[0] = 305419896L;

	ctx->keys[1] = 591751049L;

	ctx->keys[2] = 878082192L;



	for (;pw_len; --pw_len)

		trad_enc_update_keys(ctx, *pw++);

	return 0;

}



static int

is_traditional_pkware_encryption_supported(void)

{

	uint8_t key[TRAD_HEADER_SIZE];



	if (archive_random(key, sizeof(key)-1) != ARCHIVE_OK)

		return (0);

	return (1);

}



static int

init_traditional_pkware_encryption(struct archive_write *a)

{

	struct zip *zip = a->format_data;

	const char *passphrase;

	uint8_t key[TRAD_HEADER_SIZE];

	uint8_t key_encrypted[TRAD_HEADER_SIZE];

	int ret;



	passphrase = __archive_write_get_passphrase(a);

	if (passphrase == NULL) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Encryption needs passphrase");

		return ARCHIVE_FAILED;

	}

	if (archive_random(key, sizeof(key)-1) != ARCHIVE_OK) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Can't generate random number for encryption");

		return ARCHIVE_FATAL;

	}

	trad_enc_init(&zip->tctx, passphrase, strlen(passphrase));

	/* Set the last key code which will be used as a check code

	 * for verifying passphrase in decryption. */

	key[TRAD_HEADER_SIZE-1] = zip->trad_chkdat;

	trad_enc_encrypt_update(&zip->tctx, key, TRAD_HEADER_SIZE,

	    key_encrypted, TRAD_HEADER_SIZE);

	/* Write encrypted keys in the top of the file content. */

	ret = __archive_write_output(a, key_encrypted, TRAD_HEADER_SIZE);

	if (ret != ARCHIVE_OK)

		return (ret);

	zip->written_bytes += TRAD_HEADER_SIZE;

	zip->entry_compressed_written += TRAD_HEADER_SIZE;

	return (ret);

}



static int

init_winzip_aes_encryption(struct archive_write *a)

{

	struct zip *zip = a->format_data;

	const char *passphrase;

	size_t key_len, salt_len;

	uint8_t salt[16 + 2];

	uint8_t derived_key[MAX_DERIVED_KEY_BUF_SIZE];

	int ret;



	passphrase = __archive_write_get_passphrase(a);

	if (passphrase == NULL) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Encryption needs passphrase");

		return (ARCHIVE_FAILED);

	}

	if (zip->entry_encryption == ENCRYPTION_WINZIP_AES128) {

		salt_len = 8;

		key_len = 16;

	} else {

		/* AES 256 */

		salt_len = 16;

		key_len = 32;

	}

	if (archive_random(salt, salt_len) != ARCHIVE_OK) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Can't generate random number for encryption");

		return (ARCHIVE_FATAL);

	}

	archive_pbkdf2_sha1(passphrase, strlen(passphrase),

	    salt, salt_len, 1000, derived_key, key_len * 2 + 2);



	ret = archive_encrypto_aes_ctr_init(&zip->cctx, derived_key, key_len);

	if (ret != 0) {

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Decryption is unsupported due to lack of crypto library");

		return (ARCHIVE_FAILED);

	}

	ret = archive_hmac_sha1_init(&zip->hctx, derived_key + key_len,

	    key_len);

	if (ret != 0) {

		archive_encrypto_aes_ctr_release(&zip->cctx);

		archive_set_error(&a->archive, ARCHIVE_ERRNO_MISC,

		    "Failed to initialize HMAC-SHA1");

		return (ARCHIVE_FAILED);

        }



	/* Set a passowrd verification value after the 'salt'. */

	salt[salt_len] = derived_key[key_len * 2];

	salt[salt_len + 1] = derived_key[key_len * 2 + 1];



	/* Write encrypted keys in the top of the file content. */

	ret = __archive_write_output(a, salt, salt_len + 2);

	if (ret != ARCHIVE_OK)

		return (ret);

	zip->written_bytes += salt_len + 2;

	zip->entry_compressed_written += salt_len + 2;



	return (ARCHIVE_OK);

}



static int

is_winzip_aes_encryption_supported(int encryption)

{

	size_t key_len, salt_len;

	uint8_t salt[16 + 2];

	uint8_t derived_key[MAX_DERIVED_KEY_BUF_SIZE];

	archive_crypto_ctx cctx;

	archive_hmac_sha1_ctx hctx;

	int ret;



	if (encryption == ENCRYPTION_WINZIP_AES128) {

		salt_len = 8;

		key_len = 16;

	} else {

		/* AES 256 */

		salt_len = 16;

		key_len = 32;

	}

	if (archive_random(salt, salt_len) != ARCHIVE_OK)

		return (0);

	ret = archive_pbkdf2_sha1("p", 1, salt, salt_len, 1000,

	    derived_key, key_len * 2 + 2);

	if (ret != 0)

		return (0);



	ret = archive_encrypto_aes_ctr_init(&cctx, derived_key, key_len);

	if (ret != 0)

		return (0);

	ret = archive_hmac_sha1_init(&hctx, derived_key + key_len,

	    key_len);

	archive_encrypto_aes_ctr_release(&cctx);

	if (ret != 0)

		return (0);

	archive_hmac_sha1_cleanup(&hctx);

	return (1);

}
