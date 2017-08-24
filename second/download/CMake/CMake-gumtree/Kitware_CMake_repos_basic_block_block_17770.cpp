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