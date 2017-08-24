{
	BCRYPT_ALG_HANDLE hAlg;
	BCRYPT_HASH_HANDLE hHash;
	DWORD hash_len;
	PBYTE hash;
	ULONG result;
	NTSTATUS status;

	ctx->hAlg = NULL;
	status = BCryptOpenAlgorithmProvider(&hAlg, BCRYPT_SHA1_ALGORITHM,
		MS_PRIMITIVE_PROVIDER, BCRYPT_ALG_HANDLE_HMAC_FLAG);
	if (!BCRYPT_SUCCESS(status))
		return -1;
	status = BCryptGetProperty(hAlg, BCRYPT_HASH_LENGTH, (PUCHAR)&hash_len,
		sizeof(hash_len), &result, 0);
	if (!BCRYPT_SUCCESS(status)) {
		BCryptCloseAlgorithmProvider(hAlg, 0);
		return -1;
	}
	hash = (PBYTE)HeapAlloc(GetProcessHeap(), 0, hash_len);
	if (hash == NULL) {
		BCryptCloseAlgorithmProvider(hAlg, 0);
		return -1;
	}
	status = BCryptCreateHash(hAlg, &hHash, NULL, 0,
		(PUCHAR)key, (ULONG)key_len, BCRYPT_HASH_REUSABLE_FLAG);
	if (!BCRYPT_SUCCESS(status)) {
		BCryptCloseAlgorithmProvider(hAlg, 0);
		HeapFree(GetProcessHeap(), 0, hash);
		return -1;
	}

	ctx->hAlg = hAlg;
	ctx->hHash = hHash;
	ctx->hash_len = hash_len;
	ctx->hash = hash;

	return 0;
}