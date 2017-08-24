{
	DWORD siglen = (DWORD)bufsize;

	if (!ctx->valid)
		return (ARCHIVE_FAILED);

	CryptGetHashParam(ctx->hash, HP_HASHVAL, buf, &siglen, 0);
	CryptDestroyHash(ctx->hash);
	CryptReleaseContext(ctx->cryptProv, 0);
	ctx->valid = 0;
	return (ARCHIVE_OK);
}