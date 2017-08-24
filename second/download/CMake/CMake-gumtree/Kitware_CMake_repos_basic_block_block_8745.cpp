{
	BCRYPT_ALG_HANDLE hAlg;
	BCRYPT_KEY_HANDLE hKey;
	DWORD keyObj_len, aes_key_len;
	PBYTE keyObj;
	ULONG result;
	NTSTATUS status;
	BCRYPT_KEY_LENGTHS_STRUCT key_lengths;

	ctx->hAlg = NULL;
	ctx->hKey = NULL;
	ctx->keyObj = NULL;
	switch (key_len) {
	case 16: aes_key_len = 128; break;
	case 24: aes_key_len = 192; break;
	case 32: aes_key_len = 256; break;
	default: return -1;
	}
	status = BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_AES_ALGORITHM,
		MS_PRIMITIVE_PROVIDER, 0);
	if (!BCRYPT_SUCCESS(status))
		return -1;
	status = BCryptGetProperty(hAlg, BCRYPT_KEY_LENGTHS, (PUCHAR)&key_lengths,
		sizeof(key_lengths), &result, 0);
	if (!BCRYPT_SUCCESS(status)) {
		BCryptCloseAlgorithmProvider(hAlg, 0);
		return -1;
	}
	if (key_lengths.dwMinLength > aes_key_len
		|| key_lengths.dwMaxLength < aes_key_len) {
		BCryptCloseAlgorithmProvider(hAlg, 0);
		return -1;
	}
	status = BCryptGetProperty(hAlg, BCRYPT_OBJECT_LENGTH, (PUCHAR)&keyObj_len,
		sizeof(keyObj_len), &result, 0);
	if (!BCRYPT_SUCCESS(status)) {
		BCryptCloseAlgorithmProvider(hAlg, 0);
		return -1;
	}
	keyObj = (PBYTE)HeapAlloc(GetProcessHeap(), 0, keyObj_len);
	if (keyObj == NULL) {
		BCryptCloseAlgorithmProvider(hAlg, 0);
		return -1;
	}
	status = BCryptSetProperty(hAlg, BCRYPT_CHAINING_MODE,
		(PUCHAR)BCRYPT_CHAIN_MODE_ECB, sizeof(BCRYPT_CHAIN_MODE_ECB), 0);
	if (!BCRYPT_SUCCESS(status)) {
		BCryptCloseAlgorithmProvider(hAlg, 0);
		HeapFree(GetProcessHeap(), 0, keyObj);
		return -1;
	}
	status = BCryptGenerateSymmetricKey(hAlg, &hKey,
		keyObj, keyObj_len,
		(PUCHAR)(uintptr_t)key, (ULONG)key_len, 0);
	if (!BCRYPT_SUCCESS(status)) {
		BCryptCloseAlgorithmProvider(hAlg, 0);
		HeapFree(GetProcessHeap(), 0, keyObj);
		return -1;
	}

	ctx->hAlg = hAlg;
	ctx->hKey = hKey;
	ctx->keyObj = keyObj;
	ctx->keyObj_len = keyObj_len;
	ctx->encr_pos = AES_BLOCK_SIZE;

	return 0;
}