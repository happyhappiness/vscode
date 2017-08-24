{
	*ctx = HMAC_CTX_new();
	if (*ctx == NULL)
		return -1;
	HMAC_Init_ex(*ctx, key, key_len, EVP_sha1(), NULL);
	return 0;
}