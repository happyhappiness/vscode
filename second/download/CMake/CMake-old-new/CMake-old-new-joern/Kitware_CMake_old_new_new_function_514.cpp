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