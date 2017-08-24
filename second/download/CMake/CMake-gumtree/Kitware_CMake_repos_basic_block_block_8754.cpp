{
	if ((ctx->ctx = EVP_CIPHER_CTX_new()) == NULL)
		return -1;

	switch (key_len) {
	case 16: ctx->type = EVP_aes_128_ecb(); break;
	case 24: ctx->type = EVP_aes_192_ecb(); break;
	case 32: ctx->type = EVP_aes_256_ecb(); break;
	default: ctx->type = NULL; return -1;
	}

	ctx->key_len = key_len;
	memcpy(ctx->key, key, key_len);
	memset(ctx->nonce, 0, sizeof(ctx->nonce));
	ctx->encr_pos = AES_BLOCK_SIZE;
	EVP_CIPHER_CTX_init(ctx->ctx);
	return 0;
}